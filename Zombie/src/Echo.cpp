#include "Echo.h"

extern std::string rcvMsg;

State* Echo::update()
{
	State* state = this;
	if (!rcvMsg.empty())
	{
		m_SrvMsg = rcvMsg.c_str();
		if (m_SrvMsg[COMMAND] == CCHANGESTATE)
		{
			if (m_SrvMsg[STATE] == ECHO)
				std::cout << "Already in Echo" << std::endl;
			else if (m_SrvMsg[STATE] == STANDBY)
			{
				std::cout << "Changed to Standby" << std::endl;
				state = new Standby(m_Zombie);
				delete this;
			}
		}
	}
	return state;
}

void Echo::run()
{
	if (!rcvMsg.empty())
	{
		m_SrvMsg = rcvMsg.c_str();
		if (m_SrvMsg[COMMAND] == CMSG)
		{
			const char* msg = &m_SrvMsg[MESSAGE];
			m_Zombie.sendToSrv(msg, strlen(msg));
		}
	}
}
