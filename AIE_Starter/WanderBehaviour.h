#pragma once
#include "Behaviour.h"
#include "agent.h"

class WanderBehaviour : public Behaviour
{
public:
	virtual void Update(Agent* agent, float deltaTime);
};

