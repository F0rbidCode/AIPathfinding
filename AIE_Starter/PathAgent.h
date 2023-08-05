#pragma once
#include <vector>
#include "pathfinding.h"
#include"raylib.h"
#include "NodeMap.h"

using namespace std;
using namespace AIForGames;

class PathAgent
{
private:
	glm::vec2 m_position; //current x,y positions of the path agent

	
	int m_currentIndex; //current index of the path
	Node* m_currentNode; //pointer to the current node the path agent is on

	float m_speed; //the speed the path agent can travel at

public:
	PathAgent() { m_speed = 64; }
	vector<Node*> m_path;
	void setNode(Node* start) { m_position = start->position, m_currentNode = start; }
	void UpdateNode(Node* start) { if(start) m_currentNode = start; } //used to update its node without moving its x,y positions
	void setSpeed(float speed) { m_speed = speed; }
	void Update(float deltaTiem);
	void GoToNode(Node* node, NodeMap* nodeMap);
	void GoToNodeD(Node* node, NodeMap* nodeMap);
	void Draw(Color color);

	//return the current node the agent is on
	Node* GetCurrentNode() { return m_currentNode; }

	//return the path agents path
	vector<Node*> GetPath() { return m_path; }

	//return path agents current position
	glm::vec2 GetPosition() { return m_position; }
};

