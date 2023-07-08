#include "PathAgent.h"
void PathAgent::GoToNode(Node* node)
{
	m_path = DijkstrasSearch(m_currentNode, node); //calculate the path to the end node
	m_currentIndex = 0; //reset the current index to 0
}

void PathAgent::Update(float deltaTime)
{
	GoToNode(m_target);
	//if path is empty return
	if (m_path.size() <= 1)
	{
	}
	else
	{

		//calculate the distance and unit vecrtor to the next node
		float distance = sqrt((m_path[m_currentIndex + 1]->position.x - m_position.x) * (m_path[m_currentIndex + 1]->position.x - m_position.x) + (m_path[m_currentIndex + 1]->position.y - m_position.y) * (m_path[m_currentIndex + 1]->position.y - m_position.y));
		//initialise the vector to hold the unit vector
		glm::vec2 unitVector;
		//calculate the vector to in the direction of the next point
		unitVector.x = m_path[m_currentIndex + 1]->position.x - m_position.x;
		unitVector.y = m_path[m_currentIndex + 1]->position.y - m_position.y;

		//calculate the magnitude of the vector
		float mag = sqrt((unitVector.x * unitVector.x) + (unitVector.y * unitVector.y));

		//calculate the unit vector
		unitVector.x = unitVector.x / mag;
		unitVector.y = unitVector.y / mag;

		//subtract speed * delta tiem from distance
		distance = distance - (m_speed * deltaTime);

		//if distance is grater then 0
		if (distance > 0)
		{
			//move closer to the next node
			m_position.x = m_position.x + (m_speed * deltaTime * unitVector.x);
			m_position.y = m_position.y + (m_speed * deltaTime * unitVector.y);
		}
		else //else if we have moved past the node
		{
			//add 1 to current index
			m_currentIndex++;
			//update the current node
			m_currentNode = m_path[m_currentIndex];
			//if we have reached the end
			if (m_path[m_currentIndex] == m_path.back())
			{
				//set out position to the end position
				m_position.x = m_path.back()->position.x;
				m_position.y = m_path.back()->position.y;
				//empty the path
				m_path.clear();
			}
			else //else if there is another node
			{
				//invert distacne so it is now positive
				distance = -distance;

				//calculate the unit vector from the previous node to the new next node
				unitVector.x = m_path[m_currentIndex + 1]->position.x - m_path[m_currentIndex]->position.x;
				unitVector.y = m_path[m_currentIndex + 1]->position.y - m_path[m_currentIndex]->position.y;

				//calculate the magnitude of the vector
				mag = sqrt((unitVector.x * unitVector.x) + (unitVector.y * unitVector.y));
				//calculate the unit vector
				unitVector.x = unitVector.x / mag;
				unitVector.y = unitVector.y / mag;

				//move along the vector to the next node by the remaining distance
				m_position.x = m_path[m_currentIndex]->position.x + (distance * unitVector.x);
				m_position.y = m_path[m_currentIndex]->position.y + (distance * unitVector.y);

			}
		}
	}
}

void PathAgent::Draw(Color color)
{
	DrawCircle((int)m_position.x, (int)m_position.y, 8, color);
}
