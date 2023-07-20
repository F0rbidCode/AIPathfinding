#pragma once
#include "Behaviour.h"
#include "raylib.h"
#include <glm/glm.hpp>

class GoToPointBehaviour : public Behaviour
{
public:
	virtual void Update(Agent* agent, float deltaTime); //overide update function
};

