#include "TcpServer.h"
#include "NetLogger.h"

#pragma comment(lib, "ws2_32")
#include <iostream>
#include <string>
#include "pch.h"
#include "framework.h"
#include "Serializer.h"
#include <mutex>

namespace DNet {
	// This is the constructor of a class that has been exported.
	CNetwork::CNetwork(int userCapacity, int serverPort) : m_serverPort(serverPort), m_networkType(ENetworkType::None)
	{
		WSADATA wsa;

		int errorCode;
		errorCode = WSAStartup(MAKEWORD(2, 2), &wsa) != 0;
		assert(errorCode == 0);

		m_cpHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	}

	CNetwork::~CNetwork()
	{
		
		NetLogger::LogInfo(L"WSACleanup");
		// 윈속 종료
		WSACancelBlockingCall();
		WSACleanup();
		CloseHandle(m_cpHandle);

		for (int i = 0; i < m_workers.size(); i++) {
			NetLogger::LogInfo(L"Join");
			m_workers[i]->join();
		}
		NetLogger::LogInfo(L"Delete Network");

	}

	bool CNetworkServer::Start()
	{
		if (m_networkType != ENetworkType::None) return false;
		m_networkType = ENetworkType::Server;
		NetLogger::LogInfo(L"start server");
		int retval;

		// crreate socket
		m_listen_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (m_listen_sock == INVALID_SOCKET)
		{

			NetLogger::LogError(WSAGetLastError(), L"error : create listen_sock");
			return false;
		}

		// bind
		SOCKADDR_IN serveraddr;
		ZeroMemory(&serveraddr, sizeof(serveraddr));
		serveraddr.sin_family = AF_INET;
		serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
		serveraddr.sin_port = htons(m_serverPort);

		const char optval = 1;
		setsockopt(m_listen_sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

		retval = bind(m_listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
		if (retval == SOCKET_ERROR)
		{
			NetLogger::LogError(WSAGetLastError(), L"error : bind");
			return false;
		}

		// listen()
		retval = listen(m_listen_sock, SOMAXCONN);
		if (retval == SOCKET_ERROR)
		{
			NetLogger::LogError(WSAGetLastError(), L"error : listen");
			return false;
		}

		StartWorker();
		return true;
	}

	void CNetworkServer::StartAccept()
	{
		// accept loop

		SOCKET client_sock;
		SOCKADDR_IN clientaddr;
		int addrlen;
		DWORD recvbytes, flags;
		while (1) {

			// accept()
			int addrlen = sizeof(clientaddr);
			client_sock = accept(m_listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
			if (client_sock == INVALID_SOCKET) {
				//err_display("accept()");
				break;
			}
			//create CP
			CreateIoCompletionPort((HANDLE)client_sock, m_cpHandle, client_sock, 0);

			// 소켓 정보 구조체 할당, 유저추가
			buf_type* socketBuf = m_bufPool.AllocObject();
			RecvOverlapped* ptr = new RecvOverlapped(socketBuf);
			if (ptr == NULL) break;
			ZeroMemory(&ptr->overlapped, sizeof(ptr->overlapped));

			User* user = m_userPool.AllocObject();
			user->csocket = client_sock;
			user->sessionId = m_users.size();
			m_users.push_back(user);
			ptr->user = user;

			if (acceptCallback != nullptr)
				acceptCallback(user->sessionId);

			//수신 시작
			PostRecv(ptr);
		}
	}

	void CNetworkServer::PostSendToUser(const char* buf, int len, User* user)
	{
		PostSend(buf, len, user->csocket);
	}

	void CNetworkServer::PostSendToSessionId(const char* buf, int len, int sessionId)
	{
		User* user = m_users[sessionId];
		PostSendToUser(buf, len, user);
	}

	User* CNetworkServer::GetUser(int sessionId)
	{
		return m_users[sessionId];
	}

	void CNetwork::WorkerThread()
	{
		bool success;
		HANDLE hcp = m_cpHandle;

		while (1) {

			//Log(1, L"Wait WorkerThread");

			// 비동기 입출력 완료 기다리기
			DWORD cbTransferred;
			SOCKET client_sock;
			OverlappedEx* pOverlapped = nullptr;
			success = GetQueuedCompletionStatus(hcp, &cbTransferred,
				(PULONG_PTR)&client_sock, (LPOVERLAPPED*)&pOverlapped, INFINITE);
			//success = GetQueuedCompletionStatus(hcp, &cbTransferred,
			//	(LPDWORD)&client_sock, (LPOVERLAPPED*)&pOverlapped, INFINITE);
			if (success == false && pOverlapped == nullptr)
			{
				NetLogger::LogError(1, L"Fail GetQueuedCompletionStatus");
				break;
			}
			switch (pOverlapped->type)
			{
			case EOverlappedType::Send:
			{
				ProcSend((SendOverlapped*)pOverlapped);
				break;
			}
			case EOverlappedType::Recv:
			{
				ProcRecv((RecvOverlapped*)pOverlapped, cbTransferred);
				break;
			}
			}

		}
	}

	void CNetwork::EnqueueMessage(buf512* buf512, int sessionId)
	{
		MutexLocker locker(_mt);
		//버퍼 삽입
		User* user = GetUser(sessionId);
		dynamic_buf& unprocessedBuffer = user->unprocessedBuffer;
		unprocessedBuffer.insert(unprocessedBuffer.end(), buf512->buf, buf512->buf + buf512->len);

		// Log(buf512->len, L"buf512->len");

		while (true) {
			if (unprocessedBuffer.size() == 0)
			{
				return;
			}
			//버퍼에서 완성된 패킷 확인
			int packetDataSize;
			const size_t headerSize = sizeof(INT32);

			//sAssert(unprocessedBuffer.data() != nullptr, L"unprocessedBuffer");
			Serializer ser(unprocessedBuffer.data(), BUFSIZE);
			ser.SetOffset(0);
			ser.Deserialize<INT32>(&packetDataSize);


			//Log(packetDataSize, L"data Size");
			//Log(m_unprocessedBuffer.size() - headerSize, L"m_unprocessedBuffer.size() - headerSize");
			if (unprocessedBuffer.size() - headerSize < packetDataSize)
				break;

			//

			//Log(1, L"Enqueue Start");
			Message message;
			message.sessionId = sessionId;
			message.buf.reserve(packetDataSize + headerSize);

			message.buf.insert(message.buf.end(), unprocessedBuffer.data() + headerSize, unprocessedBuffer.data() + packetDataSize + headerSize);


			size_t eraseSize = packetDataSize + headerSize;
			if (eraseSize > unprocessedBuffer.size()) {
				//sAssert(false, L"erase error 101");
				return;
			}

			unprocessedBuffer.erase(unprocessedBuffer.begin(), unprocessedBuffer.begin() + eraseSize);

			//Log(m_unprocessedBuffer.size(), L"m_unprocessedBuffer.size()");

			m_messageQueue.push(message);
			//Log(m_messageQueue.size(), L"message queue size(enqueue)");





			//Log(message.buf.size(), L"Enqueue Packet byte");
		}
	}

	void CNetwork::ProcSend(SendOverlapped* sendOverlapped)
	{
		//Log(1, L"ProcSend");
		m_sendOverlappedPool.ReturnObject(sendOverlapped);
	}

	void CNetwork::ProcRecv(RecvOverlapped* recvOverlapped, DWORD cbTransferred)
	{
		bool success = true; // fix
#pragma region  GetClientInfo

		SOCKADDR_IN clientaddr;
		int addrlen = sizeof(clientaddr);
		getpeername(recvOverlapped->user->csocket, (SOCKADDR*)&clientaddr, &addrlen);
		// 비동기 입출력 결과 확인
		if (success == false || cbTransferred == 0) {
			if (success == false) {
				DWORD temp1, temp2;
				WSAGetOverlappedResult(recvOverlapped->user->csocket, &recvOverlapped->overlapped,
					&temp1, FALSE, &temp2);
				//err_display("WSAGetOverlappedResult()");
			}
			closesocket(recvOverlapped->user->csocket);

			if (closeCallback != nullptr)
				closeCallback(recvOverlapped->user->sessionId);
			//recv closeCallback return
			return;
		}
#pragma endregion

#pragma region ProcPacket
		recvOverlapped->pbuf->len = cbTransferred;

		if (recvOverlapped->wsabuf.len == BUFSIZE) {

			recvOverlapped->wsabuf.len = cbTransferred;
			EnqueueMessage(recvOverlapped->pbuf, recvOverlapped->user->sessionId);
			//Log(1,L"Recv Enqueue End");
		}
#pragma endregion
		PostRecv(recvOverlapped);
	}


	void CNetwork::ProcMessage()
	{
		//Log(1, L"Proc Start");
		while (true)
		{
			Message message;

			{
				MutexLocker locker(_mt);

				//Log(m_messageQueue.size(), L"message queue size(dequeue)");

				if (m_messageQueue.empty()) return;
				message = m_messageQueue.front();
				m_messageQueue.pop();
			}

			//Log(1, L"Proc Meesage");


			if (messageCallback != nullptr) {
				//sAssert(message.buf.size() != 0);
				messageCallback(message.buf.data(), message.buf.size(), message.sessionId);
			}

		}
		return;
	}

	CNetworkClient::CNetworkClient(int serverPort) : CNetwork(0, serverPort)
	{
	}

	CNetworkClient::~CNetworkClient()
	{

		//Log(1, L"Delete CNetworkClient");
	}

	bool CNetworkClient::Connect(const char* ip)
	{
		if (m_networkType != ENetworkType::None) return false;
		m_networkType = ENetworkType::Client;
		//Log(0, L"start client");

		//create socket
		SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sock == INVALID_SOCKET)
		{
			//Log(-1, L"error : create socket");
			return false;
		}
		//Log(0, L"success create socket");

		//connect
		sockaddr_in serv_adr;
		memset(&serv_adr, 0, sizeof(serv_adr));
		serv_adr.sin_family = AF_INET;
		serv_adr.sin_addr.s_addr = inet_addr(ip);
		serv_adr.sin_port = htons(m_serverPort);

		int connectResult = connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr));
		if (connectResult == -1)
		{
			//Log(-1, L"error : connect");
			return false;
		}
		//Log(0, L"success connect");

		//create CP
		CreateIoCompletionPort((HANDLE)sock, m_cpHandle, sock, 0);

		// 소켓 정보 구조체 할당, 유저추가
		buf_type* socketBuf = m_bufPool.AllocObject();
		RecvOverlapped* ptr = new RecvOverlapped(socketBuf);
		ZeroMemory(&ptr->overlapped, sizeof(ptr->overlapped));
		m_user.csocket = sock;
		ptr->user = &m_user;


		//수신 시작
		PostRecv(ptr);

		StartWorker();

		return true;

	}

	void CNetworkClient::PostSendToServer(const char* buf, int len)
	{
		PostSend(buf, len, m_user.csocket);
	}


	User* CNetworkClient::GetUser(int sessionId)
	{
		return &m_user;
	}

	ENetworkType CNetwork::GetNetowrkType()
	{
		return m_networkType;
	}

	CNetworkServer::CNetworkServer(int userCapacity, int serverPort) : CNetwork(userCapacity, serverPort), m_users()
	{
		m_users.reserve(userCapacity);
	}

	CNetworkServer::~CNetworkServer()
	{
		closesocket(m_listen_sock);
		//Log(1, L"Delete NetworkServer");
	}

	void CNetwork::PostSend(const char* buf, int len, SOCKET sock)
	{
		SendOverlapped* sendOverlap = m_sendOverlappedPool.AllocObject();
		ZeroMemory(&sendOverlap->overlapped, sizeof(sendOverlap->overlapped));

		const int headerSize = sizeof(INT32);
		dynamic_buf& sendBuf = sendOverlap->sendBuf;
		sendBuf.resize(headerSize + len);

		Serializer serializer(sendBuf.data(), headerSize + len);
		serializer.SetOffset(0);
		serializer.Serialize<INT32>(len);
		serializer.SerializeBytes(buf, 0, len);

		sendOverlap->wsabuf.buf = sendBuf.data();
		sendOverlap->wsabuf.len = len + headerSize;
		DWORD sendbytes;
		int retval = WSASend(sock, &sendOverlap->wsabuf, 1,
			&sendbytes, 0, &sendOverlap->overlapped, NULL);
		//Log(sendbytes, L"Sended");
		if (retval == SOCKET_ERROR) {
			if (WSAGetLastError() != WSA_IO_PENDING) {
			}
			return;
		}
	}

	void CNetwork::StartWorker()
	{
		// CPU 개수 확인
		SYSTEM_INFO si;
		GetSystemInfo(&si);

		// (CPU 개수 * 2)개의 작업자 스레드 생성
		int workerThreadSize = (int)si.dwNumberOfProcessors * 2;

		for (int i = 0; i < workerThreadSize; i++) {
			m_workers.push_back(new std::thread(&CNetworkServer::WorkerThread, this));
		}

	}
	User* CNetwork::GetUser(int sessionId)
	{
		return nullptr;
	}
	void CNetwork::PostRecv(RecvOverlapped* recvOverlapped)
	{
		//
		// 데이터 받기
		ZeroMemory(&recvOverlapped->overlapped, sizeof(recvOverlapped->overlapped));
		recvOverlapped->ChangeBuf(m_bufPool.AllocObject());
		DWORD recvbytes;
		DWORD flags = 0;
		bool success = WSARecv(recvOverlapped->user->csocket, &recvOverlapped->wsabuf, 1,
			&recvbytes, &flags, &recvOverlapped->overlapped, NULL);
		//cout << flags << endl;
		if (success == SOCKET_ERROR) {
			if (WSAGetLastError() != WSA_IO_PENDING) {
				//err_display("WSARecv()");
			}//
			return;
		}
	}

	RecvOverlapped::RecvOverlapped(buf512* buf) : OverlappedEx(EOverlappedType::Recv)
	{
		ChangeBuf(buf);
	}

	void RecvOverlapped::ChangeBuf(buf512* buf)
	{
		pbuf = buf;
		wsabuf.buf = pbuf->buf;
		wsabuf.len = BUFSIZE;
	}

	SendOverlapped::SendOverlapped() : OverlappedEx(EOverlappedType::Send), wsabuf()
	{
	}

	OverlappedEx::OverlappedEx(EOverlappedType t) : type(t)
	{
	}

}