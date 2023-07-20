#include "Agent.h"
#include "Behaviour.h"

void Agent::Update(float deltaTime)
{
	if (m_current)//if current behaviour not = NULL
	{
		//call update on current behaviour
		m_current->Update(this, deltaTime);
	}
	//call update on pathing agent
	m_pathAgent.Update(deltaTime);
}

void Agent::GoTo(glm::vec2 point)
{
	Node* end = m_nodeMap->GetClosestNode(point);
	m_pathAgent.GoToNode(end);
}

bool Agent::PathComplete()
{
	return m_pathAgent.GetPath().empty();
}
