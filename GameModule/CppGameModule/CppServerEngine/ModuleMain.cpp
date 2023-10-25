/*
vcpkg install physX:x64-windows
vcpkg install jsoncpp:x64-windows
*/

#pragma comment(lib,"DUtil/DUtil.lib")
#pragma comment(lib,"DGameLogic/DGameLogic.lib")
#include "../DGameLogic/Framework/LogicMain.h"
//#include "../DNetwork/TcpServer.h"
#include "../DGameLogic/DConfig.h"

#include <iostream>
#include <thread>
#include <cstdlib>

//DNet::CNetworkServer* server;
void OnLogging(DDebug::Logger::Level _level, const char* _message)
{
	std::cout << "OnLogging " << _message << std::endl;
}
void onAccept(int _session_id) {
	std::cout << "OnAccept " << _session_id << std::endl;
}

void onClose(int _session_id) {
	std::cout << "OnClose " << _session_id << std::endl;

}

int onMessage(char* _buf, int _len, int _session_id) {
	std::cout << "OnMessage " << _len << " / " << _session_id << std::endl;
	//server->PostSendToSessionId(_buf, _len, _session_id);
	return 0;
}
void runLogicMain()
{
	DDebug::Logger::getInstance().subscribe([](DDebug::Logger::Level _level, const char* _message) {
		OnLogging(_level, _message);
		});

	DLOG_INFO("dd");
	DLogic::LogicMain logic_main;
	logic_main.Init();
	logic_main.Start();
	for (int i = 0; i < 100; i++) {
		logic_main.Update(0);
	}
}
/*
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
*/
int main() {
	DConfig::getInstance()->Load(R"(C:\Users\HP\Documents\CppServerEngine\CppServerEngine\x64\Debug\config.json)");
	//std::thread network_thread(runNetMain);
	//network_thread.join();

	//std::thread logic_thread(runLogicMain);

	//logic_thread.join();
	runLogicMain();
}


//-GameLogic
//	-Geometrys
//		-Physics
//			-GenericLib
//				-math

//시리얼라이저
//패킷처리