#pragma once
#include <vector>
#include "pathfinding.h"
#include"raylib.h"

using namespace std;
using namespace AIForGames;

class PathAgent
{
private:
	glm::vec2 m_position;

	
	int m_currentIndex;
	Node* m_currentNode;

	float m_speed;

public:
	PathAgent() { m_speed = 64; }
	vector<Node*> m_path;
	void setNode(Node* start) { m_position = start->position, m_currentNode = start; }
	void setSpeed(float speed) { m_speed = speed; }
	void Update(float deltaTiem);
	void GoToNode(Node* node);
	void Draw();

	//return the current node the agent is on
	Node* GetCurrentNode() { return m_currentNode; }

	//return the path agents path
	vector<Node*> GetPath() { return m_path; }

	//return path agents current position
	glm::vec2 GetPosition() { return m_position; }
};

