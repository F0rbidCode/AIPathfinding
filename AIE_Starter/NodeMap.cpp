#include "NodeMap.h"

//destructor
NodeMap:: ~NodeMap()
{
	//loop through the nodes and delete each node
	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			delete GetNode(x, y);
		}
	}
	delete m_nodes;
	m_nodes = nullptr;
}

void NodeMap::Initialise(std::vector<std::string> asciiMap, int cellSize)
{
	m_cellSize = cellSize;
	const char emptySquare = '0';

	//we will assume all the strings are the same length, so we will size the map according to the number of strings and the length of the first one
	m_height = asciiMap.size(); //set the height to the size of the vector
	m_width = asciiMap[0].size(); //set the width to the size of the first string in the vector

	m_nodes = new Node * [m_width * m_height]; //create an array of nodes the size of height * width

	//loop over the strings, creating Node entries as we go
	for (int y = 0; y < m_height; y++)
	{
		std::string& line = asciiMap[y]; //set the current line to the current position in the ascii map
		//tell the user that they have a miss-matched strign length
		if (line.size() != m_width)
		{
			std::cout << "Missmatched line #" << y << " in ASCII map (" << line.size() << " instead of " << m_width << " )" << std::endl;
		}

		for (int x = 0; x < m_width; x++)
		{
			//get the x-th character, or return an empty node if the string isnt long enough
			char tile = x < line.size() ? line[x] : emptySquare;

			//create a node for anything but a '.' character
			m_nodes[x + m_width * y] = tile == emptySquare ? nullptr : new Node(((float)x + 0.5f) * m_cellSize, ((float)y + 0.5f)* m_cellSize);
		}
	}

	//now loop over the nodes creating connections between each node and its neighbour to the west and south on the grid. this will link up all nodes
	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			Node* node = GetNode(x, y);
			if (node)
			{
				//see if there is a node to our west, checking for array overruns
				//first if we are on the west-most edge
				Node* nodeWest = x == 0 ? nullptr : GetNode(x - 1, y);
				if (nodeWest)
				{
					node->ConnectTo(nodeWest, 1); //TODO weights
					nodeWest->ConnectTo(node, 1);
				}

				//see if there is a node to our south checking for array index overruns again
				Node* nodeSouth = y == 0 ? nullptr : GetNode(x, y - 1);
				if (nodeSouth)
				{
					node->ConnectTo(nodeSouth, 1);
					nodeSouth->ConnectTo(node, 1);
				}
			}
		}
	}
}

void NodeMap::Draw()
{
	Color cellColor;
	cellColor.a = 255;
	cellColor.r = 255;
	cellColor.g = 0;
	cellColor.b = 0;

	Color lineColor = GRAY;

	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			Node* node = GetNode(x, y);
			if (node == nullptr)
			{
				//draw a solid block in empty squares without a navigation node
				DrawRectangle((int)(x * m_cellSize), (int)(y * m_cellSize), (int)m_cellSize - 1, (int)m_cellSize - 1, cellColor);
			}
			else
			{
				//draw the connections between the node and its neighbours
				for (int i = 0; i < node->connections.size(); i++)
				{
					Node* other = node->connections[i].target;
					DrawLine((x + 0.5f) * m_cellSize, (y + 0.5f) * m_cellSize, (int)other->position.x, (int)other->position.y, lineColor);
				}
			}
		}
	}
}

void NodeMap::DrawPath(std::vector<Node*> path)
{
	Color lineColor = WHITE;

	for (int i = 1; i < path.size(); i++)
	{
		DrawLine(path[i - 1]->position.x, path[i - 1]->position.y, path[i]->position.x, path[i]->position.y, lineColor);
	}
}

//function used to get the closes node to the mouse curser
Node* NodeMap::GetClosestNode(glm::vec2 worldPos)
{
	int i = (int)(worldPos.x / m_cellSize);
	if (i < 0 || i >= m_width) return nullptr;

	int j = (int)(worldPos.y / m_cellSize);
	if (j < 0 || j >= m_width) return nullptr;

	return GetNode(i, j);
}


//function to return a random node
Node* NodeMap::GetRandomNode()
{
	//initialise a node pointer
	Node* node = nullptr;
	while (node == nullptr)
	{
		//get random x and y coordinates
		int x = rand() % m_width;
		int y = rand() % m_height;
		//get a node at those points
		node = GetNode(x, y);
	}
	return node;
}

//function used to togle nodes between walled off and path
Node* NodeMap::ToggleClosesNode(glm::vec2 worldPos, vector<string>& ascIIMap)
{
	const char emptyNode = '0';
	const char fullNode = '1';

	int i = (int)(worldPos.x / m_cellSize);
	if (i < 0 || i >= m_width) return nullptr;

	int j = (int)(worldPos.y / m_cellSize);
	if (j < 0 || j >= m_width) return nullptr;

	if (ascIIMap[j][i] == emptyNode)
	{
		ascIIMap[j][i] = fullNode;
	}
	else
	{
		ascIIMap[j][i] = emptyNode;
	}
}
