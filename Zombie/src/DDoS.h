#pragma once

#include "State.h"

class DDoS : public State
{
public:
	DDoS();
	~DDoS();
	State* update() override;
	void run() override;
private:
};