#include "Standby.h"

extern std::string rcvMsg;

State* Standby::update()
{
	State* state = this;
	if (!rcvMsg.empty())
	{
		m_SrvMsg = rcvMsg.c_str();
		if (m_SrvMsg[COMMAND_INDEX] == CCHANGESTATE)
		{
			if(m_SrvMsg[STATE_INDEX] == STANDBY)
				std::cout << "Already in Standby" << std::endl;
			else if (m_SrvMsg[STATE_INDEX] == ECHO)
			{
				std::cout << "Changed to Echo" << std::endl;
				state = new Echo(m_Zombie);
				delete this;
			}
		}
	}
	return state;
}

void Standby::run()
{
	if (!rcvMsg.empty())
	{
		m_SrvMsg = rcvMsg.c_str();
		if (m_SrvMsg[COMMAND_INDEX] == CEXIT)
			setExit(true);
	}
	//DO nothing
}
