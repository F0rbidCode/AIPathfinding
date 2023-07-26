#include "State.h"
#include "Behaviour.h"


State::~State()
{
	for (Behaviour* b : m_behaviours) delete b;

	for (Transition t : m_transitions) delete t.condition;
}

void State::Update(Agent* agent, float deltaTime)
{
	//call update on all behaviours in the m_behaviours vector, passing in the agent and delta time
	for (Behaviour* b : m_behaviours) b->Update(agent, deltaTime);
}

void State::AddTransition(DistanceCondition* DC, State* s)
{
	Transition t;

	t.condition = DC;
	t.targetState = s;

	m_transitions.push_back(t);
}
