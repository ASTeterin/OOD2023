#ifndef FLYWITHWINGS_H
#define FLYWITHWINGS_H

#include "IFlyBehavior.h"
#include <iostream>

class FlyWithWings : public IFlyBehavior
{
public:
	void Fly() override
	{
		std::cout << "I'm flying with wings!!" << std::endl;
		this->CountFligth();
	}

private:
	int m_flightCounter = 0;
	void CountFligth()
	{
		std::cout << "Number of fligth: " << ++m_flightCounter << std::endl;
	}
};

#endif
