#pragma once
#include "Behaviour.h"


class WanderBehaviour : public Behaviour
{
public:
	virtual void Update(Agent* agent, float deltaTime);

	void Enter(Agent* agent);

	//evaluate used for UtilityAI
	float Evaluate(Agent* agent);
};

