#pragma once

#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#include <string>


class Client
{
public:
	Client();
	~Client();

	bool init();
	int cleanup();

	bool createSocket();
	bool connectToSrv(const std::string& srvIp, int srvPort);

	bool sendToSrv(const std::string& msg);
	bool receiveFromServer();

	std::string getMessage();

private:
	SOCKET m_Client;

	char m_Buf[4096];
};