#pragma once
#include "Behaviour.h"
class Condition
{
public:
	virtual bool IsTrue(Agent* agent) = 0;
};

