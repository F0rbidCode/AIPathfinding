#pragma once
#include "PathAgent.h"
#include "NodeMap.h"


class Behaviour;

class Agent
{
public:
	Agent() {}
	Agent(NodeMap* _nodeMap, Behaviour* _behaviour); /*: m_current(_behaviour), m_nodeMap(_nodeMap), m_color({ 255, 255, 0, 255 }) { m_current->Enter(this); }*/
	
	~Agent() { delete m_current; }

	void Update(float deltaTime);
	void Draw() { m_pathAgent.Draw(m_color); };
	void setNode(Node* start) { m_pathAgent.setNode(start); }
	void UpdateNode(Node* start) { m_pathAgent.UpdateNode(start); } //used to update the path agents node without it changing its x,y position
	void setSpeed(float speed) { m_pathAgent.setSpeed(speed); }
	void setColor(Color color) { m_color = color; }
	void setTarget(Agent* target) { m_target = target; }
	void GoTo(glm::vec2 point);
	void GoTo(Node* node) { m_pathAgent.GoToNode(node); };

	//helper function to report when path is complete
	bool PathComplete();

	//function to return the nodeMap
	NodeMap* getNodeMap() { return m_nodeMap; }

	//function to return the target agent
	Agent* GetTarget() { return m_target; }
	glm::vec2 GetTargetPos() { return m_targetPos; }

	//function to get the position of the pathAgent
	glm::vec2 GetPosition() { return m_pathAgent.GetPosition(); }
	//function to get the current node of the agent
	Node* GetCurrentNode() { return m_pathAgent.GetCurrentNode(); }

	//function to reset and clear the agents path
	void Reset() { m_pathAgent.GetPath().clear(); }

private:
	PathAgent m_pathAgent;
	Behaviour* m_current;
	NodeMap* m_nodeMap;
	Color m_color;

	//pointer to a target agent
	Agent* m_target;
	glm::vec2 m_targetPos;
};

