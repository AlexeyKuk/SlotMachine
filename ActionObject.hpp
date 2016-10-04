/*
 * ActionObject.hpp
 *
 *  Created on: Oct 3, 2016
 *      Author: alex
 */

#pragma once

#include <memory>
#include <chrono>

#include "CanvasObject.hpp"
#include "CanvasObjectFactory.hpp"
#include "SlotState.hpp"

class ActionObject
{
public:

	virtual void on_click() = 0;

	virtual bool is_clicked(float xCoord, float yCoord) const = 0;

	virtual void draw() = 0;

	virtual ~ActionObject() {}

};



class StartButton : public ActionObject
{
	enum t_drawState
	{
		DRAW_STATE_INVISIBLE
		, DRAW_STATE_BLINK1
		, DRAW_STATE_BLINK2
		, DRAW_STATE_IN_PROGRESS
		, DRAW_STATE_NOT_ENABLE
	};

public:
	StartButton(float i_x, float i_y, float i_width, float i_height
				,SlotState* i_slot_state
				,CanvasObject * i_drawState1
				,CanvasObject * i_drawState2 )
		: x(i_x), y(i_y), width(i_width), height(i_height)
			, slotState(i_slot_state)
			, drawState1(i_drawState1)
			, drawState2(i_drawState2)
	{}

	/*virtual*/
	void on_click() override;

	/*virtual*/
	bool is_clicked(float xCoord, float yCoord) const override;

	/*virtual*/
	void draw() override;

private:
	void blink();

private:
	float x, y;
	float width, height;

	SlotState * slotState;

	std::unique_ptr<CanvasObject> drawState1;
	std::unique_ptr<CanvasObject> drawState2;
	t_drawState currentDrawState {DRAW_STATE_BLINK1};

	bool isTimePointInitialized {false};
	std::chrono::steady_clock::time_point tpPrevTime;

	double durNextBlink 	{0.4}; //sec
	double remainToBlink 	{0.0}; //sec
};
