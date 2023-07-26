#pragma once
class Agent;

class Behaviour
{
public:
	virtual void Enter(Agent* agent) {}
	virtual void Update(Agent* agent, float deltaTime) = 0;
	virtual void Exit(Agent* agent) {}

	//used by UtilityAI to determin which behaviour to do
	virtual float Evaluate(Agent* agent) { return 0.0f; }
};