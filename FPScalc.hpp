/*
 * FPScalc.hpp
 *
 *  Created on: Oct 5, 2016
 *      Author: alex
 */

#pragma once


class FPScalc
{
public:
	void add_cadr(double duration)
	{
		++cadrs;
		timeSpent += duration;
		if (timeSpent > 1.0)
		{
			prevFPS = cadrs / timeSpent;
			cadrs = 0;
			timeSpent = 0.0;
		}
	}

	double get_fps() { return prevFPS; }

private:

	double 		prevFPS 	{0.0};
	unsigned 	cadrs 		{0};
	double		timeSpent 	{0.0}; // in sec
};
