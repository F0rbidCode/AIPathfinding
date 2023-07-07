#include "Pathfinding.h"

void AIForGames::Node::ConnectTo(Node* other, float cost)
{
	connections.push_back(Edge(other, cost));
}

//compare function for sorting the vectors by gScore
bool AIForGames::CompareGScore(Node*& first, Node*& second)
{ 
	return first->gScore < second->gScore;
}
//compare function for sorting the vectors by fScore
bool AIForGames::CompareFScore(Node*& first, Node*& second)
{
	return first->fScore < second->fScore;
}

//function to calculate the hScore
float AIForGames::Heuristic(Node* current, Node* end)
{
	return ((end->position.x - current->position.x) * (end->position.x - current->position.x) + (end->position.y - current->position.y) * (end->position.y - current->position.y));
}


std::vector<AIForGames::Node*> AIForGames::DijkstrasSearch(Node* startNode, Node* endNode)
{
	
	std::vector<Node*> path;

	//make sure input if valid
	if (!startNode || !endNode)
	{
		std::cout << "start and end nodes were not valid " << std::endl;
		return path;
	}

	if (startNode == endNode)
	{
		std::cout << "the start node was the same as the end node" << std::endl;
		return path;
	}

	//Initialise the starting node
	startNode->gScore = 0;
	startNode->previous = NULL;

	//inistialise the tempoary list of nodes
	std::vector<Node*> open;
	std::vector<Node*> closed;

	Node* currentNode;

	//add start node to list of open nodes
	open.push_back(startNode);

	//while open list is not empty
	while (!open.empty())
	{
		//sort open list by gScore
		sort(open.begin(), open.end(), CompareGScore);

		//set current node to the first node in the open list
		currentNode = open.front();
		
		//end early if we finded the end node
		//by sorting the list first we garentee the shortest path is found providing there is no negative costs, this optamises performance but wont always guarantee the shortest path
		
		if (currentNode == endNode)
		{
			//exit the while loop
			break;
		}

		//remove the current node from the open list
		open.erase(std::find(open.begin(), open.end(), currentNode));
		//add current node to closed list
		closed.push_back(currentNode);

		//find all connectiosn in the current node
		//std::vector<Edge> c = currentNode->connections;

		for (auto c : currentNode->connections)
		{
			//is the target of the current connection is not in the closed list
			if (std::find(closed.begin(), closed.end(), c.target) == closed.end())
			{
				float gScore = currentNode->gScore + c.cost; //???????

				//the node has  not been viseted yet, calculate the gscore and update its parant, then also add it to the open list
				if (std::find(open.begin(), open.end(), c.target) == open.end()) //if the target is not in the open list
				{
					//set the targets gScore to the calculated gScore
					c.target->gScore = gScore;
					//set the previous to the current node
					c.target->previous = currentNode;
					//add the target to the open list
					open.push_back(c.target);
				}
				//if the node is already in the open list
				// compare the calculated score with the existing score to find the shorter path
				else if (gScore < c.target->gScore) //if the calculated gScore is lower then the existing one
				{
					//set the targets gScore to the calculated gScore
					c.target->gScore = gScore;
					//set the previous to the current node
					c.target->previous = currentNode;

				}
			}
		}

	}

	//create a path in reverse from the endNode to the startNode
	//set current node to endNode
	currentNode = endNode;

	//loop through untill current node == NULL
	while(currentNode != NULL)
	{
		//add the current node to the begining of the path
		path.insert(path.begin(), currentNode);
		//set the current node to its previous
		currentNode = currentNode->previous;
	}

	//return the path
	return path;
}


std::vector<AIForGames::Node*> AIForGames::AStarSearch(Node* startNode, Node* endNode)
{

	std::vector<Node*> path;

	//make sure input if valid
	if (!startNode || !endNode)
	{
		std::cout << "start and end nodes were not valid " << std::endl;
		return path;
	}

	if (startNode == endNode)
	{
		std::cout << "the start node was the same as the end node" << std::endl;
		return path;
	}

	//Initialise the starting node
	startNode->gScore = 0;
	startNode->previous = NULL;

	//inistialise the tempoary list of nodes
	std::vector<Node*> open;
	std::vector<Node*> closed;

	Node* currentNode;

	//add start node to list of open nodes
	open.push_back(startNode);

	//while open list is not empty
	while (!open.empty())
	{
		//sort open list by fScore instead of gScore
		sort(open.begin(), open.end(), CompareFScore);

		//set current node to the first node in the open list
		currentNode = open.front();

		//end early if we finded the end node
		//by sorting the list first we garentee the shortest path is found providing there is no negative costs, this optamises performance but wont always guarantee the shortest path

		if (currentNode == endNode)
		{
			//exit the while loop
			break;
		}

		//remove the current node from the open list
		open.erase(std::find(open.begin(), open.end(), currentNode));
		//add current node to closed list
		closed.push_back(currentNode);

		//find all connectiosn in the current node
		//std::vector<Edge> c = currentNode->connections;

		for (auto c : currentNode->connections)
		{
			//is the target of the current connection is not in the closed list
			if (std::find(closed.begin(), closed.end(), c.target) == closed.end())
			{
				float gScore = currentNode->gScore + c.cost;
				float hScore = Heuristic(c.target, endNode);
				float fScore = gScore + hScore;

				//the node has  not been viseted yet, calculate the gscore and update its parant, then also add it to the open list
				if (std::find(open.begin(), open.end(), c.target) == open.end()) //if the target is not in the open list
				{
					//set the targets gScore to the calculated gScore
					c.target->gScore = gScore;
					c.target->fScore = fScore;
					//set the previous to the current node
					c.target->previous = currentNode;
					//add the target to the open list
					open.push_back(c.target);
				}
				//if the node is already in the open list
				// compare the calculated fScore with the existing fScore to find the shorter path
				else if (fScore < c.target->fScore) //if the calculated gScore is lower then the existing one
				{
					//set the targets gScore to the calculated gScore
					c.target->gScore = gScore;
					c.target->fScore = fScore;
					//set the previous to the current node
					c.target->previous = currentNode;

				}
			}
		}

	}

	//create a path in reverse from the endNode to the startNode
	//set current node to endNode
	currentNode = endNode;

	//loop through untill current node == NULL
	while (currentNode != NULL)
	{
		//add the current node to the begining of the path
		path.insert(path.begin(), currentNode);
		//set the current node to its previous
		currentNode = currentNode->previous;
	}

	//return the path
	return path;
}