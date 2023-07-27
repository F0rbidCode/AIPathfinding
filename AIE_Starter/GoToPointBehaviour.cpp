#include "GoToPointBehaviour.h"
#include "Agent.h"

void GoToPointBehaviour::Update(Agent* agent, float deltaTime)
{
	
	//read mouseclicks, left for start node, right for end node
	if (IsMouseButtonPressed(0))
	{
		Vector2 mousePos = GetMousePosition(); //get the mouse position
		agent->UpdateNode(agent->getNodeMap()->GetClosestNode(agent->GetPosition())); //reset the current node of the agent to the closest node to its x, y position
		agent->GoTo(glm::vec2(mousePos.x, mousePos.y)); //call agents go to passing in the mouse position
	}
}
