/*
vcpkg install physX:x64-windows
vcpkg install jsoncpp:x64-windows
*/

#pragma comment(lib,"DGameLogic/DGameLogic.lib")
#pragma comment(lib,"DNetwork/DNetwork.lib")
#include "../DGameLogic/Framework/LogicMain.h"
#include "../DNetwork/TcpServer.h"
#include "../DGameLogic/DConfig.h"

#include <iostream>
#include <thread>
#include <cstdlib>

DNet::CNetworkServer* server;

void onAccept(int _session_id) {
	std::cout << "OnAccept " << _session_id << std::endl;
}

void onClose(int _session_id) {
	std::cout << "OnClose " << _session_id << std::endl;

}

int onMessage(char* _buf, int _len, int _session_id) {
	std::cout << "OnMessage " << _len << " / " << _session_id << std::endl;
	server->PostSendToSessionId(_buf, _len, _session_id);
	return 0;
}
void runLogicMain()
{
	DLogic::LogicMain logic_main;
	logic_main.Init();
	logic_main.Start();
}

void runNetMain()
{
	server = new DNet::CNetworkServer(100, DConfig::getInstance()->server_port);
	server->acceptCallback = onAccept;
	server->closeCallback = onClose;
	server->messageCallback = onMessage;
	server->Start();

	std::thread network_thread(&DNet::CNetworkServer::StartAccept, server);

	while (true) {
		server->ProcMessage();
	}
}

int main() {
	DConfig::getInstance()->Load(R"(C:\Users\HP\Documents\CppServerEngine\CppServerEngine\x64\Debug\config.json)");
	std::thread network_thread(runNetMain);
	//network_thread.join();

	std::thread logic_thread(runLogicMain);

	logic_thread.join();
}


//-GameLogic
//	-Geometrys
//		-Physics
//			-GenericLib
//				-math

//시리얼라이저
//패킷처리