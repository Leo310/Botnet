#pragma once

//Packetstructure	
#define COMMAND 0
//wenn COMMAND = CHANGESTATE dann ist an zweiter stelle STATE
#define STATE 1
#define MESSAGE 1

//Comands
#define CCHANGESTATE '1'
#define CMSG '2'

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

};