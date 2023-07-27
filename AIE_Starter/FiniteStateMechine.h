#pragma once
#include "Behaviour.h"
//#include "Agent.h"
#include "State.h"
class FiniteStateMechine : public Behaviour
{
private:
	std::vector<State*> m_states; //vector to hold states

	State* m_currentState; //pointer to the current state
	State* m_newState; //pointer to the next state

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

