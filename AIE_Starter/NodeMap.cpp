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
			if (tile == '2') //check if the tile being made should be a end tile
			{
				m_nodes[x + m_width * y]->isEnd = true; //if so set isEnd to true
			}
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

				//diagonals - look to (-1, -1)
				//check that there is a node to the south west
			Node* nodeSouthWest = (x == 0 || y == 0) ? nullptr : GetNode(x - 1, y - 1);

			if (nodeSouthWest)
			{
				node->ConnectTo(nodeSouthWest, 1.414f); //TODO weights
				nodeSouthWest->ConnectTo(node, 1.414f);
			}

			// and (+1,-1)
			//check that there is a node to the south east
			Node* nodeSouthEast = (x == m_width - 1 || y == 0) ? nullptr : GetNode(x + 1, y - 1);
			if (nodeSouthEast)
			{
				node->ConnectTo(nodeSouthEast, 1.414f);
				nodeSouthEast->ConnectTo(node, 1.414f);
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

	Color endColor = GREEN;

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
				if (node->isEnd)//check if the tile being drawn is the end tile
				{
					//draw the end tile
					DrawRectangle((int)(x * m_cellSize), (int)(y * m_cellSize), (int)m_cellSize - 1, (int)m_cellSize - 1, endColor); 
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
	const char EndNode = '2';

	int i = (int)(worldPos.x / m_cellSize);
	if (i < 0 || i >= m_width) return nullptr;

	int j = (int)(worldPos.y / m_cellSize);
	if (j < 0 || j >= m_width) return nullptr;

	if (ascIIMap[j][i] == EndNode)
	{
		ascIIMap[j][i] == EndNode;
	}
	else if (ascIIMap[j][i] == emptyNode)
	{
		ascIIMap[j][i] = fullNode;
	}
	else
	{
		ascIIMap[j][i] = emptyNode;
	}
}


//function to check if a node is visable from annother node
bool NodeMap::IsVisableFrom(Node* start, Node* end)
{
	//calculate a vector from start to end that is one cellsize in length
	Vector2 delta = Vector2Subtract(end->position, start->position);
	float distance = glm::distance(end->position, start->position);
	Vector2 Fulldelta = Vector2Scale(delta, m_cellSize / distance);

	//vreate a vector to store half the cell size
	Vector2 halfDelta = Vector2Scale (delta, (m_cellSize /2) / distance);

	// step forward in that direction one cell at a time from start towards end
	///instead of 1 cell at a time only go by half cell at a time
	for (float cells = 1.0f; cells < distance / (m_cellSize / 2); cells += 1.0f)
	{
		glm::vec2 testPosition = Vector2Add(start->position, Vector2Scale(halfDelta, cells));

		//if the square below is unpassable then we dont have line of sight from start to end
		if (GetClosestNode(testPosition) == nullptr)
			return false;
	}

	//we've traveled the whole path without an obstacle
	return true;
}

//helper functions for checking if nodes are visable
Vector2 NodeMap::Vector2Subtract(glm::vec2 start, glm::vec2 end)
{ 
	Vector2 distance;
	distance.x = start.x - end.x; 
	distance.y = start.y - end.y; 
	return distance; 
}

Vector2 NodeMap::Vector2Scale(Vector2 delta, float scaler)
{
	delta.x = delta.x * scaler;
	delta.y = delta.y * scaler;

	return delta;
}

glm::vec2 NodeMap::Vector2Add(glm::vec2 first, Vector2 second)
{
	first.x = first.x + second.x;
	first.y = first.y + second.y;

	return first;
}

//function to smooth a path
vector<Node*> NodeMap::SmoothPath(vector<Node*> path)
{
	if (!path.empty())
	{
		for (int i = 0; i < (path.size() -1); i++) //loop over the full path except the last node
		{
			for (int j = i + 3; j < path.size(); j++) //loop over the the full path starting 2 ahead of i
			{
				if (IsVisableFrom(path[i], path[j])) //check if the next node is visible from the current one
				{

					path.erase(path.begin() + (j - 1)); //if it is delete the next node
					j--; //decrease j by 1 to account for the deleted node
				}
			}
		}

		////////////////////////////////////////////
		/////BUGGY
		////////////////////////////////////////////
			//Node* currentNode = path.front(); //create a pointer to the current node
			//int i = 1; //used to iterate through the path
			//Node* lastVisable = path[i+1]; //pointer to the last visable node

			//
			//while (lastVisable != path.back())
			//{			
			//	if (IsVisableFrom(currentNode, lastVisable))
			//	{
			//		path.erase(path.begin() + i);
			//	}
			//	else
			//	{
			//		currentNode = lastVisable;
			//		i++;
			//	}
			//	lastVisable = path[i+1];
			//}


	return path; //return pat
		
	}
	else //if the path is empty
	{
		path.clear(); //clear path
		return path; //return the empty path
	}

}