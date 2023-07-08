#pragma once
#include <vector>
#include "pathfinding.h"
#include"raylib.h"

using namespace AIForGames;

class PathAgent
{
private:
	glm::vec2 m_position;

	int m_currentIndex;
	Node* m_currentNode;
	Node* m_target;

	float m_speed;

public:
	std::vector<Node*> m_path;
	void setNode(Node* start) { m_position = start->position, m_currentNode = start; }
	void setTarget(Node* end) { m_target = end; }
	void setSpeed(float speed) { m_speed = speed; }
	void Update(float deltaTiem);
	void GoToNode(Node* node);
	void Draw(Color color);

	//return the current node the agent is on
	Node* GetCurrentNode() { return m_currentNode; }
	Node* GetTarget() { return m_target; }
	glm::vec2 GetPosition() { return m_position; }

};

