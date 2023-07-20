#pragma once
#include "PathAgent.h"
#include "NodeMap.h"

class Behaviour;

class Agent
{
public:
	Agent() {}
	Agent(NodeMap* _nodeMap, Behaviour* _behaviour) : m_current(_behaviour), m_nodeMap(_nodeMap), m_color({ 255, 255, 0, 255 }) {}
	~Agent() { delete m_current; }

	void Update(float deltaTime);
	void Draw() { m_pathAgent.Draw(); };
	void setNode(Node* start) { m_pathAgent.setNode(start); }
	void GoTo(glm::vec2 point);
	void GoTo(Node* node) { m_pathAgent.GoToNode(node); };

	//helper function to report when path is complete
	bool PathComplete();

	//function to return the nodeMap
	NodeMap* getNodeMap() { return m_nodeMap; }

private:
	PathAgent m_pathAgent;
	Behaviour* m_current;
	NodeMap* m_nodeMap;
	Color m_color;
};

