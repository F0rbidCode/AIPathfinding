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
};

