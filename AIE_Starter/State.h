#pragma once
#include <vector>
#include "Condition.h"
#include "DistanceCondition.h"

class Behaviour; //forward decleration of behaviour class

using namespace std;
class State
{
public:
	struct Transition
	{
		Condition* condition; //pointer to the condition of the transition
		State* targetState; //pointer to the state the transition will move to
	};

private:
	vector<Behaviour*>  m_behaviours; //vectore of behaviours the state will access
	std::vector<Transition> m_transitions; //vector of transitions to move between states

public:
	State();
	State(Behaviour* behaviour) { m_behaviours.push_back(behaviour); }
	~State();
	virtual void Enter(Agent* agent) { m_behaviours.front()->Enter(agent); };
	virtual void Update(Agent* agent, float deltaTime);
	virtual void Exit(Agent* agent) { m_behaviours.back()->Exit(agent); };

	//function to add Transitions
	void AddTransition(DistanceCondition* DC, State* s);

	//function to return behaviours
	vector<Behaviour*> GetBehaviours() { return m_behaviours; }

	//function to return the vector of transitions
	std::vector<Transition> GetTransitions() { return m_transitions; }
};

