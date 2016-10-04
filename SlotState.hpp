/*
 * SlotState.hpp
 *
 *  Created on: Oct 4, 2016
 *      Author: alex
 */

#pragma once

#include <vector>


class SlotState
{
public:
	SlotState(unsigned i_wheels, float i_maxShift = 1.0f
				, float shiftValInit = 0.0f
				, float speedValInit = 0.0f
				, float slowingValInit = 0.3f
				, float delayedValInit = 2.0f)
		: 	maxShift(i_maxShift)
			, shift(i_wheels, shiftValInit)
			, speed(i_wheels, speedValInit)
			, slowing(i_wheels, slowingValInit)
			, delayed(i_wheels, delayedValInit)
	{
		initSpeed = speed;
		initSlowing = slowing;
		initDelayed = delayed;
	}


	std::vector<bool> turn(double duration);

	bool is_stopped();

	void set_speed(std::vector<float>&& setVal) 	{ initSpeed = std::move(setVal);  }
	void set_slowing(std::vector<float>&& setVal)	{ initSlowing = std::move(setVal);}
	void set_delayed(std::vector<float>&& setVal)	{ initDelayed = std::move(setVal);}

	float get_shift(unsigned wheel) const 	{ return shift[wheel]; }
	float get_speed(unsigned wheel) const	{ return speed[wheel]; }
	float get_slowing(unsigned wheel) const	{ return slowing[wheel]; }


	void roll()
	{
		speed = initSpeed;
		slowing = initSlowing;
		delayed = initDelayed;
	}

private:
	double calc_delayed(unsigned wheel, double duration);


private:
	float maxShift;

	std::vector<float> shift;
	std::vector<float> speed;
	std::vector<float> slowing;
	std::vector<float> delayed;

	std::vector<float> initSpeed;
	std::vector<float> initSlowing;
	std::vector<float> initDelayed;

	float hitchSpeed {0.6f};
};
