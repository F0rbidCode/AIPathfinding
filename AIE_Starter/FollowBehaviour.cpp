#include "FollowBehaviour.h"
//#include "Agent.h"

namespace AIForGames
{
	void FollowBehaviour::Update(Agent* agent, float deltaTime)
	{
		//check if the agent has moved significantly from its last position, if so repath towards it
		Agent* target = agent->GetTarget();

		float dist = glm::distance(target->GetPosition(), lastTargetPosition); //calculate the distance between targets curront position and the targets last position
		if (dist > agent->getNodeMap()->GetCellSize());//if the distance is gater then the cell size
		{
			lastTargetPosition = target->GetPosition();
			agent->GoTo(lastTargetPosition);
		}
	}


	void FollowBehaviour::Enter(Agent* agent)
	{
		//red when following
		agent->setColor({ 255,0,0,255 });
		agent->Reset();
	}

	float FollowBehaviour::Evaluate(Agent* agent)
	{
		Agent* target = agent->GetTarget(); //get the target of the agent
		float dist = glm::distance(target->GetPosition(), agent->GetPosition()); //get the distance between the agent and its target

		float eval = 10 * agent->getNodeMap()->GetCellSize() - dist; //calculate the eval score bassed on the number of cells between the agent and its target

		if (eval < 0) //if eval is greater then 0
		{
			eval = 0; //set eval to 0
		}
		return eval; //return the evaluated score
	}
}
