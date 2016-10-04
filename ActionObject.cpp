/*
 * ActionObject.cpp
 *
 *  Created on: Oct 4, 2016
 *      Author: alex
 */

#include "ActionObject.hpp"

void StartButton::on_click()
{
//	currentDrawState = (currentDrawState == DRAW_STATE1) ? DRAW_STATE2 : DRAW_STATE1;
	if (currentDrawState == DRAW_STATE_BLINK1 ||
			currentDrawState == DRAW_STATE_BLINK2)
	{
		slotState->roll();
		currentDrawState = DRAW_STATE_IN_PROGRESS;
	}
}

bool StartButton::is_clicked(float xCoord, float yCoord) const
{
	if (	xCoord >= x && yCoord >= y
		&& 	xCoord <= x + width && yCoord <= y + height)
		return true;

	return false;
}

#include <iostream>

void StartButton::blink()
{
	// initialize time point
	if (!isTimePointInitialized)
	{
		tpPrevTime = std::chrono::steady_clock::now();
		isTimePointInitialized = true;
		return;
	}

	// get current timepoint
	std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();

	std::chrono::duration<double> duration =
			std::chrono::duration_cast<std::chrono::duration<double>>(t2 - tpPrevTime);

	if (currentDrawState == DRAW_STATE_BLINK1
			|| currentDrawState == DRAW_STATE_BLINK2)
	{
		// update time to next blink
		if (remainToBlink > duration.count())
		{
			remainToBlink -= duration.count();
		}
		else
		{
			remainToBlink = durNextBlink - (remainToBlink - duration.count());

			if (remainToBlink < 0.0)
			{
				remainToBlink = 0.0;
			}
			else
			{
				//change state
				currentDrawState = (currentDrawState == DRAW_STATE_BLINK1) ?
										DRAW_STATE_BLINK2
									:	DRAW_STATE_BLINK1;
			}
		}
	}
	// save current timepoint as previous
	tpPrevTime = t2;

}


void StartButton::draw()
{
	blink();

	switch(currentDrawState)
	{
	case DRAW_STATE_BLINK1:
		drawState1->draw(0.0f, 0.0f);
		break;

	case DRAW_STATE_IN_PROGRESS:
		drawState1->draw(0.0f, 0.0f);

		if (slotState->is_stopped())
			currentDrawState = DRAW_STATE_BLINK1;

		break;

	case DRAW_STATE_BLINK2:
		drawState2->draw(0.0f, 0.0f);
		break;

	case DRAW_STATE_NOT_ENABLE:
		drawState2->draw(0.0f, 0.0f);
		break;

	case DRAW_STATE_INVISIBLE:
		break;
	}
}

