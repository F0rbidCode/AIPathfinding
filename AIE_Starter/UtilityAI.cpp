#include "UtilityAI.h"

UtilityAI::~UtilityAI()
{
	//delete all behaviours in the m_behaviours vector
	for (Behaviour* b : m_behaviours)
	{
		delete b;
	}
}

void UtilityAI::Update(Agent* agent, float deltaTime)
{
	float bestEval = 0;
	Behaviour* newBehaviour = nullptr;
	//loop through all the behaviours in vector m_behabiours
	for (Behaviour* b : m_behaviours)
	{
		float eval = b->Evaluate(agent); //crate a new float and set it to the result of Evaluate on the current behaviour
		if (eval > bestEval) //check if the current eval is greater then the best eval
		{
			bestEval = eval; //set best eval to the eqal eval
			newBehaviour = b; //set the new behaviour to be the current behaviour
		}
	}

	if (newBehaviour != nullptr && newBehaviour != currentBehaviour) //check that we have set a new behaviour and is not the same as the current behaviour
	{
		if (currentBehaviour)
		{
			currentBehaviour->Exit(agent); //call exit on the current behaviour
		}
		currentBehaviour = newBehaviour; //set current behaviour to the new behaviour
		currentBehaviour->Enter(agent); //call enter on the current behaviour
	}

	currentBehaviour->Update(agent, deltaTime); //call update on the current behaviour
}
