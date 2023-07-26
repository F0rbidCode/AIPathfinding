#pragma once
#include "Condition.h"

class DistanceCondition : public Condition
{
private:
	float m_distance;
	bool m_lessThan;

public:
	DistanceCondition(float d, bool It) :m_distance(d), m_lessThan(It) {}
	virtual bool IsTrue(Agent* agent);
};

