#include "WanderBehaviour.h"

void WanderBehaviour::Update(Agent* agent, float deltaTime)
{
	if (agent->PathComplete())
	{
		agent->GoTo(agent->getNodeMap()->GetRandomNode());
	}
}
