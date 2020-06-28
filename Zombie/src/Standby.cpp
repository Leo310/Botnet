#include "Standby.h"

extern bool rcvdMsg;

State* Standby::update()
{
	State* state = this;
	if (rcvdMsg)
	{
		m_SrvMsg = m_Zombie.getSrvMsg();
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
	rcvdMsg = false;
}
