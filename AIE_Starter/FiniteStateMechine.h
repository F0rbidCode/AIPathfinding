#pragma once
#include "Behaviour.h"
//#include "Agent.h"
#include "State.h"
class FiniteStateMechine : public Behaviour
{
private:
	std::vector<State*> m_states;

	State* m_currentState;
	State* m_newState;

public:
	FiniteStateMechine(State* s) : m_currentState(s), m_newState(nullptr) {}

	virtual ~FiniteStateMechine();

	void Update(Agent* agent, float deltaTime);

	//function to add state to FSM
	void AddState(State* state);

	//function to get current state
	State* GetCurrentState() { return m_currentState; }

	void Enter(Agent* agent);
};

