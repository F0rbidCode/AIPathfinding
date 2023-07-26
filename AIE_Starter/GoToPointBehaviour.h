#pragma once
#include "Behaviour.h"
#include "raylib.h"
#include <glm/glm.hpp>
//#include "Agent.h"

class GoToPointBehaviour : public Behaviour
{
public:
	virtual void Update(Agent* agent, float deltaTime); //overide update function
};

