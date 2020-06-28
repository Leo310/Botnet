#pragma once

//Packetstructure	
#define COMMAND_INDEX 0
//wenn COMMAND = CHANGESTATE dann ist an zweiter stelle STATE
#define STATE_INDEX 1
#define MESSAGE_INDEX 1

//Comands
#define CEXIT '1'
#define CCHANGESTATE '2'
#define CMSG '3'

//states
#define STANDBY '1'
#define ECHO '2'
#define DDOS '3'

#include "Client.h"
#include <atomic>

class State
{
public:
	State() {};
	virtual ~State() {};

	virtual State* update() = 0;
	virtual void run() = 0;

	virtual void setExit(bool exit);
	virtual bool getExit();
private:
	bool m_Exit = false;
};