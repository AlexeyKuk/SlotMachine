/*
 * SlotState.cpp
 *
 *  Created on: Oct 4, 2016
 *      Author: alex
 */

#include <cmath>

#include "SlotState.hpp"


double SlotState::calc_delayed(unsigned wheel, double duration)
{
	double remain = 0.0;

	if (delayed[wheel] == 0.0) return duration;

	if (delayed[wheel] > duration)
	{
		delayed[wheel] -= duration;
	}
	else
	{
		remain = duration - delayed[wheel];
		delayed[wheel] = 0.0;
	}

	return remain;
}



std::vector<bool> SlotState::turn(double duration)
{
	std::vector<bool> isNeedNextSlot(shift.size(), false);

	for (std::size_t i = 0; i < shift.size(); ++i)
	{
		// do step for a wheel
		if (speed[i] > 0.0f)
			shift[i] += duration * speed[i];
		else if (shift[i] > 0.0) // if need to hitch on placeholder
			shift[i] += duration * hitchSpeed;

		double remainDuration = calc_delayed(i, duration);

		// decreasing wheel's speed
		double nextSpeed = speed[i] - slowing[i] * remainDuration;
		speed[i] = (nextSpeed  > 0) ? nextSpeed : 0;

		if (shift[i] > maxShift)
		{
			shift[i] = (speed[i] > 0.0f) ? std::fmod(shift[i], maxShift) : 0.0f;
			isNeedNextSlot[i] = true;
		}
	}

	return isNeedNextSlot;
}


bool SlotState::is_stopped()
{
	for (std::size_t i = 0; i < shift.size(); ++i)
	{
		if (shift[i] != 0.0f || speed[i] != 0.0f)
			return false;
	}

	return true;
}


