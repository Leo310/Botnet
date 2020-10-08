#pragma once

class Client
{
public:
	Client();
	~Client();

	bool init();

	bool createSocket();
	bool connectToSrv(const char* srvIp, int srvPort);
	void closeConnection1();
	bool closeConnection2();

	bool sendToSrv(const char* msg, int size);
	bool receiveFromServer();

	const char* getSrvMsg();

private:
	SOCKET m_Client;

	char m_Buf[4096];
};