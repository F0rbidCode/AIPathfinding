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

//evaluate used for UtilityAI
float WanderBehaviour::Evaluate(Agent* agent)
{
	Agent* target = agent->GetTarget(); //get the agents target
	float dist = glm::distance(target->GetPosition(), agent->GetPosition()); // calculate the distance to target

	float eval = dist; //set the eval score to distance

	if (eval < 0)//if ecal is less then 0
	{
		eval = 0; //set eval to 0
	}
	
	return eval; //return the eval score
}
