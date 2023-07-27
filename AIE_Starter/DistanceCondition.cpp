#include "DistanceCondition.h"
#include <glm/glm.hpp>
#include "Agent.h"
bool DistanceCondition::IsTrue(Agent* agent)
{
	//return true if the distance between the agent and its target is less then m_distance
	return(glm::distance(agent->GetPosition(), agent->GetTarget()->GetPosition()) < m_distance) == m_lessThan;
}
