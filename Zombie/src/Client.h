#pragma once

#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#include "Packet.h"

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
	
	void closeConnection1();
	bool closeConnection2();

	bool sendToSrv(const Packet& packet);
	
	bool receiveFromServer();
	const Packet* getSrvPacket();

private:
	SOCKET m_Client;

	Packet m_RcvdPacket;
	bool m_RcvdMsg = false;
};