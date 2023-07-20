#include "FollowBehaviour.h"
#include "Agent.h"

namespace AIForGames
{
	void FollowBehaviour::Update(Agent* agent, float deltaTime)
	{
		//check if the agent has moved significantly from its last position, if so repath towards it
		Agent* target = agent->getTarget();

		float dist = glm::distance(target->GetPosition(), lastTargetPosition); //calculate the distance between targets curront position and the targets last position
		if (dist > agent->getNodeMap()->GetCellSize());//if the distance is gater then the cell size
		{
			lastTargetPosition = target->GetPosition();
			agent->GoTo(lastTargetPosition);
		}
	}
}
