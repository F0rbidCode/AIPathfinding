#include "FiniteStateMechine.h"

FiniteStateMechine::~FiniteStateMechine()
{
	for (State* s : m_states) delete s;
}

void FiniteStateMechine::Update(Agent* agent, float deltaTime)
{
	State* newState = nullptr; //create a pointer to a new state and set it to null

	//check the current state's transitions
	for (State::Transition t : m_currentState->GetTransitions()) //check through all transitions stored in the current states transitions
	{
		if(t.condition->IsTrue(agent)) //if the conditions for transition is true
		{
			newState = t.targetState; //set the new state to the transitions target state
		}
		//if we change states, clean up the old one and initialise the new one
		if (newState != nullptr && newState != m_currentState) //if new state is not = nullptr or current state
		{
			m_currentState->Exit(agent); //call exit on the current state
			m_currentState = newState; //set current state to the new state
			m_currentState->Enter(agent); //call enter on current state
		}
		//update the current state
		m_currentState->Update(agent, deltaTime); //call upadate on current state
	}
}

void FiniteStateMechine::AddState(State* state)
{
	m_states.push_back(state); //push the passed in state to the array of states
}

void FiniteStateMechine::Enter(Agent* agent)
{
	m_currentState->Enter(agent);//call enter on the current state
}