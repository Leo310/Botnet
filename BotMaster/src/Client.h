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

private:
	SOCKET m_Client;
};