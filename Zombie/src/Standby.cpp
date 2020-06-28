#include "Standby.h"

extern std::string rcvMsg;

State* Standby::update()
{
	State* state = this;
	if (!rcvMsg.empty())
	{
		m_SrvMsg = rcvMsg.c_str();
		if (m_SrvMsg[COMMAND] == CCHANGESTATE)
		{
			if(m_SrvMsg[STATE] == STANDBY)
				std::cout << "Already in Standby" << std::endl;
			else if (m_SrvMsg[STATE] == ECHO)
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
	//DO nothing
}
