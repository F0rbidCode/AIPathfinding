#pragma once
#include "Behaviour.h"
#include "Agent.h"

namespace AIForGames
{
	class FollowBehaviour : public Behaviour
	{
	private:
		glm::vec2 lastTargetPosition;
	public:
		virtual void Update(Agent* agent, float deltaTime);
		
		void Enter(Agent* agent);

		//evaluate used for UtilityAI
		float Evaluate(Agent* agent);
	};
}

