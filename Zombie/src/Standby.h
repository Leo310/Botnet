#pragma once

#include "State.h"
#include "Echo.h"

class Standby : public State
{
public:
	Standby(Client& zombie) 
		: m_Zombie(zombie) {};
	~Standby() {};
	State* update() override;
	void run() override;
private:
	Client& m_Zombie;
	const char* m_SrvMsg = nullptr;
};