#ifndef DANCE_WALTZ_H
#define DANCE_WALTZ_H

#include "IDanceBehavor.h"
#include <iostream>

class DanceWaltz : public IDanceBehavior
{
public:
	void Dance() override
	{
		std::cout << "I'm dancing a waltz!" << std::endl;
	}
};

#endif
#pragma once
