#include "Echo.h"

extern bool rcvdMsg;

State* Echo::update()
{
	State* state = this;
	if (rcvdMsg)
	{
		m_SrvMsg = m_Zombie.getSrvMsg();
		if (m_SrvMsg[COMMAND] == CCHANGESTATE)
		{
			if (m_SrvMsg[STATE] == STANDBY)
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
	if (rcvdMsg)
	{
		m_SrvMsg = m_Zombie.getSrvMsg();
		if (m_SrvMsg[COMMAND] == CMSG)
		{
			const char* msg = &m_SrvMsg[MESSAGE];
			m_Zombie.sendToSrv(msg, strlen(msg));
		}
	}
	rcvdMsg = false;
}
