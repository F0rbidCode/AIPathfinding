#include "SelectorBehaviour.h"
#include "Agent.h"

//update function
void SelectorBehaviour::Update(Agent* agent, float deltaTime)
{
	if (glm::distance(agent->GetPosition(), agent->GetTarget()->GetPosition()) < agent->getNodeMap()->GetCellSize() * 5)
	{
		SetBehaviour(m_b1, agent);
		agent->setColor({ 255,0,0,255 });
	}
	else
	{
		SetBehaviour(m_b2, agent);
		agent->setColor({ 0, 255, 255, 255 });
	}
	m_selected->Update(agent, deltaTime);
}

//function to set the Behaviour
void SelectorBehaviour::SetBehaviour(Behaviour* b, Agent* agent)
{
	if (m_selected != b)//check that the selected behaviour is not the same as the behaviour we are switching to
	{
		m_selected = b; //set the selected behavoir to the behavoir we want to switch to
		agent->Reset(); //reset the agent to follow the new behaviour
	}
}
