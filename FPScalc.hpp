/*
 * FPScalc.hpp
 *
 *  Created on: Oct 5, 2016
 *      Author: alex
 */

#pragma once

#include <chrono>
#include <string>
#include <GL/glut.h>
#include <GL/gl.h>

#include "constants.hpp"

/*
 * FPScalc
 * 		calculates average value of FPS with 1 sec updating
 */
class FPScalc
{
	using time_point = std::chrono::steady_clock::time_point;
	using t_duration = std::chrono::duration<double>;

public:
	void add_cadr()
	{
		if (!isTimePointInitialized)
		{
			prevTime = get_now();
			isTimePointInitialized = true;
			return;
		}

		// calc time spent between adjacent cadrs
		time_point timeNow = get_now();
		double duration = t_duration(timeNow - prevTime).count();

		// accumulate cadrs and spent time
		++cadrs;
		timeSpent += duration;

		// calc average value for fps in 1 sec
		if (timeSpent > 1.0)
		{
			prevFPS = cadrs / timeSpent;
			cadrs = 0;
			timeSpent = 0.0;
		}

		// set new time point as prev
		prevTime = timeNow;
	}

	double get_fps() const { return prevFPS; }

private:

	time_point get_now() const { return std::chrono::steady_clock::now(); }

private:

	double 		prevFPS 	{0.0};
	unsigned 	cadrs 		{0};
	double		timeSpent 	{0.0}; // in sec

	bool isTimePointInitialized	{false};
	time_point prevTime;
};



class DrawFPS
{
public:
	static void draw(const FPScalc& fps)
	{
		std::string str("fps = ");
		str += std::to_string(fps.get_fps());

		glLoadIdentity();
		float * p_DRAW_FPS_POS = CONFIG.get_DRAW_FPS_POS();
		glRasterPos3f(p_DRAW_FPS_POS[0], p_DRAW_FPS_POS[1], p_DRAW_FPS_POS[2]);

		for (auto e : str)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, e);
		}
	}
};




