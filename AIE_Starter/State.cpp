#include "State.h"
#include "Behaviour.h"


State::~State()
{
	for (Behaviour* b : m_behaviours) delete b; //delete all behaviours in m_behaviours

	for (Transition t : m_transitions) delete t.condition; //delete all conditions stored in each transition in m_transitions
}

void State::Update(Agent* agent, float deltaTime)
{
	//call update on all behaviours in the m_behaviours vector, passing in the agent and delta time
	for (Behaviour* b : m_behaviours) b->Update(agent, deltaTime);
}

void State::AddTransition(Condition* C, State* s)
{
	Transition t; //create new transtion

	t.condition = C; //set condition to past in condition
	t.targetState = s; //set target state to passed in state

	m_transitions.push_back(t); //push transition to m_transitions
}
