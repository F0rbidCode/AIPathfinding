#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Pathfinding.h"
#include "raylib.h"

using namespace AIForGames;
using namespace std;

class NodeMap
{
	int m_width, m_height; //height and width of the node map
	float m_cellSize; //size of each cell

	Node** m_nodes; 

public:
	~NodeMap();//destructor

	void Initialise(std::vector<std::string> ascIIMap, int cellSize);

	Node* GetNode(int x, int y) { return m_nodes[x + m_width * y]; } //helper function to return a node from the node map

	void Draw(); //draw the map onscreen
	void DrawPath(std::vector<Node*> path);

	//function used to get the closes node to the mouse curser
	Node* GetClosestNode(glm::vec2 worldPos);

	//function to return a random navigatable node
	Node* GetRandomNode();

	//function to return cell size
	float GetCellSize() { return m_cellSize; }


	//function used to togle nodes between walled off and path
	Node* ToggleClosesNode(glm::vec2 worldPos, vector<string>& ascIIMap);

	//function to check if a node is visable from annother node
	bool IsVisableFrom(Node* start, Node* end);


	//helper functions for checking if nodes are visable
	Vector2 Vector2Subtract(glm::vec2 start, glm::vec2 end);
	glm::vec2 Vector2Add(glm::vec2 first, Vector2 second);
	Vector2 Vector2Scale(Vector2 delta, float scaler);

	//function to smooth a path
	vector<Node*> SmoothPath(vector<Node*> path);
};

