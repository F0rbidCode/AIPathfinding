#pragma once
#include "Behaviour.h"
//#include "Agent.h"
class SelectorBehaviour : public Behaviour
{
private:
	Behaviour* m_b1;
	Behaviour* m_b2;
	Behaviour* m_selected;

public:
	SelectorBehaviour(Behaviour* b1, Behaviour* b2) : m_b1(b1), m_b2(b2) {}
	~SelectorBehaviour() { delete m_b1; m_b1 = nullptr; delete m_b2; m_b2 = nullptr; }
	virtual void Update(Agent * agent, float deltaTime);

	//function to set the Behaviour
	void SetBehaviour(Behaviour* b, Agent* agent);
};

