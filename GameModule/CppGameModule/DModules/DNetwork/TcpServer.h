#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32")

#include "DNetwork.h"
#include <WinSock2.h>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>

namespace DNet {
	#define BUFSIZE 512

	typedef int(__stdcall* Win32Callback)(int value1, const wchar_t* text1);
	typedef int(__stdcall* MessageCallback)(char* buf, int len, int sessionId);
	typedef void(__stdcall* AcceptCallback)(int sessionId);
	typedef void(__stdcall* CloseCallback)(int sessionId);
	typedef void(__stdcall* NetEventCallback)();
	typedef std::vector<char> dynamic_buf;

	struct buf512
	{
		char buf[BUFSIZE + 1];
		int len;
	};

	class User
	{
	public:
		SOCKET csocket;
		int sessionId;
		dynamic_buf unprocessedBuffer;
	public:
		User() : csocket(NULL), sessionId(0) {}
		~User() { if (csocket != NULL) closesocket(csocket); }
	};


	enum class EOverlappedType
	{
		Send,
		Recv
	};
	enum class ENetworkType
	{
		Client,
		Server,
		None
	};

	class OverlappedEx
	{
	public:
		OverlappedEx(EOverlappedType);
	public:
		OVERLAPPED overlapped;
		EOverlappedType type;
	};

	class RecvOverlapped : public OverlappedEx
	{
	public:
		RecvOverlapped(buf512* buf);
		void ChangeBuf(buf512*);
	public:
		buf512* pbuf;
		User* user;
		WSABUF wsabuf;
	};
	class SendOverlapped : public OverlappedEx
	{
	public:
		SendOverlapped();
	public:
		std::vector<char> sendBuf;
		WSABUF wsabuf;
	};

	class Message
	{
	public:
		dynamic_buf buf;
		int sessionId;
	};


	class CNetwork
	{
	public:
		typedef buf512 buf_type;
	public:
		CNetwork(int userCapacity, int serverPort);
		~CNetwork();
		void WorkerThread();
		void ProcMessage();
		ENetworkType GetNetowrkType();
	protected:
		void EnqueueMessage(buf512* buf, int sessionId);
		void PostRecv(RecvOverlapped* recvOverlapped);
		void ProcSend(SendOverlapped* sendOverlapped);
		void ProcRecv(RecvOverlapped* recvOverlapped, DWORD cbTransferred);
		void PostSend(const char* buf, int len, SOCKET sock);
		void StartWorker();
		virtual User* GetUser(int sessionId);
	public:
		MessageCallback messageCallback = nullptr;
		AcceptCallback closeCallback;

	protected:
		HANDLE m_cpHandle;
		unsigned int m_serverPort;


		std::queue<Message> m_messageQueue;
		DGeneric::CObjectPool<buf_type> m_bufPool;
		DGeneric::CObjectPool<SendOverlapped> m_sendOverlappedPool;
		std::vector <std::thread*> m_workers;

		std::recursive_mutex _mt;
		ENetworkType m_networkType;
	};

	class CNetworkServer : public CNetwork
	{
	public:
		CNetworkServer(int userCapacity, int serverPort);
		~CNetworkServer();
		bool Start();
		void StartAccept();
		void PostSendToUser(const char* buf, int len, User* user);
		void PostSendToSessionId(const char* buf, int len, int userIndex);

		virtual User* GetUser(int sessionId);
	public:
		AcceptCallback acceptCallback;

	private:


		std::vector<User*> m_users;
		DGeneric::CObjectPool<User> m_userPool;
		SOCKET m_listen_sock;

	};
	class CNetworkClient : public CNetwork
	{
	public:
		CNetworkClient(int serverPort);
		~CNetworkClient();
		bool Connect(const char* ip);
		void PostSendToServer(const char* buf, int len);
		virtual User* GetUser(int sessionId);

	public:
		NetEventCallback disconnectCallback;
	private:
		User m_user;

	};

}

