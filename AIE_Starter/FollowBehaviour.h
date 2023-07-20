#pragma once
#include "Behaviour.h"
#include "agent.h"

namespace AIForGames
{
	class FollowBehaviour : public Behaviour
	{
	private:
		glm::vec2 lastTargetPosition;
	public:
		virtual void Update(Agent* agent, float deltaTime);

	};
}

