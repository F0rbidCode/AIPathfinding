#include "FiniteStateMechine.h"

FiniteStateMechine::~FiniteStateMechine()
{
	for (State* s : m_states) delete s;
}

void FiniteStateMechine::Update(Agent* agent, float deltaTime)
{
	State* newState = nullptr;

	//check the current state's transitions
	for (State::Transition t : m_currentState->GetTransitions())
	{
		if(t.condition->IsTrue(agent))
		{
			newState = t.targetState;
		}
		//if we change states, clean up the old one and initialise the new one
		if (newState != nullptr && newState != m_currentState)
		{
			m_currentState->Exit(agent);
			m_currentState = newState;
			m_currentState->Enter(agent);
		}
		//update the current state
		m_currentState->Update(agent, deltaTime);
	}
}

void FiniteStateMechine::AddState(State* state)
{
	m_states.push_back(state);
}

void FiniteStateMechine::Enter(Agent* agent)
{
	m_currentState->Enter(agent);
}