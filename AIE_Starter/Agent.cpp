#include "Agent.h"
#include "Behaviour.h"

Agent::Agent(NodeMap* _nodeMap, Behaviour* _behaviour) : m_current(_behaviour), m_nodeMap(_nodeMap), m_color({ 255, 255, 0, 255 }) { m_current->Enter(this); }

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
	m_targetPos = point;
	Node* end = m_nodeMap->GetClosestNode(point);//find the closest node to the past in point
	m_pathAgent.GoToNode(end); //call goToNode pasing in the end node
}

bool Agent::PathComplete()
{
	return m_pathAgent.GetPath().empty(); //check if the path is empty
}
