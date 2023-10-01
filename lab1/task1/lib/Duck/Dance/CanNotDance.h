#pragma once
#ifndef CAN_NOT_DANCE_H
#define CAN_NOT_DANCE_H

#include "IDanceBehavor.h"
#include <iostream>

class CanNotDance : public IDanceBehavior
{
public:
	void Dance() override
	{
		std::cout << "I can not dance!" << std::endl;
	}
};

#endif
#pragma once
