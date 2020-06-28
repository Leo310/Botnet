#pragma once

#include "State.h"
#include "Standby.h"

class Echo : public State
{
public:
	Echo(Client& zombie)
		: m_Zombie(zombie) {};
	~Echo() {};
	State* update() override;
	void run() override;
private:
	Client& m_Zombie;
	const char* m_SrvMsg = nullptr;
};