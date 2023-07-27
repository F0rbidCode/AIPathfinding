#pragma once
#include "Behaviour.h"
#include <vector>

using namespace std;

class UtilityAI : public Behaviour
{
private:
	vector<Behaviour*> m_behaviours; //vector of accessable behaviours
	Behaviour* currentBehaviour; //pointer to current behaviour

public:

	UtilityAI() {};
	~UtilityAI();

	virtual void Update(Agent* agent, float deltaTime);

	//function to add behaviours to the vector of behaviours
	void AddBehaviour(Behaviour* b) { m_behaviours.push_back(b); } //push the passed in behaviour to m_behaviours
};

