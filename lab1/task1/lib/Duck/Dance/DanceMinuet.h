#ifndef DANCE_MINUET_H
#define DANCE_MINUET_H

#include "IDanceBehavor.h"
#include <iostream>

class DanceMinuet : public IDanceBehavior
{
public:
	void Dance() override
	{
		std::cout << "I'm dancing a minuet!" << std::endl;
	}
};

#endif
#pragma once
