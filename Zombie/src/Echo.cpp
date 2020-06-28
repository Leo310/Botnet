#include "Echo.h"

extern std::string rcvMsg;

State* Echo::update()
{
	State* state = this;
	if (!rcvMsg.empty())
	{
		m_SrvMsg = rcvMsg.c_str();
		if (m_SrvMsg[COMMAND_INDEX] == CCHANGESTATE)
		{
			if (m_SrvMsg[STATE_INDEX] == ECHO)
				std::cout << "Already in Echo" << std::endl;
			else if (m_SrvMsg[STATE_INDEX] == STANDBY)
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

		if (m_SrvMsg[COMMAND_INDEX] == CEXIT)
			setExit(true);
		else if (m_SrvMsg[COMMAND_INDEX] == CMSG)
		{
			const char* msg = &m_SrvMsg[MESSAGE_INDEX];
			m_Zombie.sendToSrv(msg, strlen(msg));
		}
	}
}
