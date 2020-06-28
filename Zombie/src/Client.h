#pragma once

#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#include <string>
#include <iostream>

class Client
{
public:
	Client();
	~Client();

	bool init();
	int cleanup();

	bool createSocket();
	bool connectToSrv(const char* srvIp, int srvPort);
	bool closeConnection();

	bool sendToSrv(const char* msg, int size);
	
	bool receiveFromServer();
	const char* getSrvMsg();
private:
	SOCKET m_Client;

	bool m_RcvdMsg = false;
	char m_Buf[4096];
};