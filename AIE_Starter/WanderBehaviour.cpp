#include "WanderBehaviour.h"
#include "Agent.h"

void WanderBehaviour::Update(Agent* agent, float deltaTime)
{
	if (agent->PathComplete())
	{
		agent->GoTo(agent->getNodeMap()->GetRandomNode());
	}
}

void WanderBehaviour::Enter(Agent* agent)
{
	agent->setColor({ 0, 255, 255, 255 });
	agent->Reset();
}
