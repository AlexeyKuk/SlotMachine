/*
 * SlotEngine.hpp
 *
 *  Created on: Sep 29, 2016
 *      Author: alex
 */

#pragma once

#include <list>
#include <memory>
#include <chrono>
#include <vector>

#include "CanvasObject.hpp"
#include "CanvasObjectFactory.hpp"
#include "ActionObject.hpp"



class SlotEngine
{
public:

	virtual void render_scene() = 0;

	virtual void animate() = 0;

	virtual void on_click(int button, int state, float x, float y) = 0;

	virtual ~SlotEngine() {}
};



class SlotState
{
public:
	SlotState(unsigned i_wheels, float i_maxShift = 1.0f
				, float shiftValInit = 0.0f
				, float speedValInit = 2.0f
				, float slowingValInit = 0.3f
				, float delayedValInit = 2.0f)
		: 	maxShift(i_maxShift)
			, shift(i_wheels, shiftValInit)
			, speed(i_wheels, speedValInit)
			, slowing(i_wheels, slowingValInit)
			, delayed(i_wheels, delayedValInit)
	{
//		initShift = shift;
		initSpeed = speed;
		initSlowing = slowing;
		initDelayed = delayed;
	}

	std::vector<bool> turn(double duration);

	void set_shift(std::vector<float>&& setVal) 	{shift = std::move(setVal); } //initShift = shift;
	void set_speed(std::vector<float>&& setVal) 	{speed = std::move(setVal); initSpeed = speed; }
	void set_slowing(std::vector<float>&& setVal)	{slowing = std::move(setVal); initSlowing = slowing;}
	void set_delayed(std::vector<float>&& setVal)	{delayed = std::move(setVal); initDelayed = delayed;}

	float get_shift(unsigned wheel) const 	{ return shift[wheel]; }
	float get_speed(unsigned wheel) const	{ return speed[wheel]; }
	float get_slowing(unsigned wheel) const	{ return slowing[wheel]; }

	void reset()
	{
//		shift = initShift;
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

//	std::vector<float> initShift;
	std::vector<float> initSpeed;
	std::vector<float> initSlowing;
	std::vector<float> initDelayed;

	float hitchSpeed {0.3f};
};


class StartButton : public ActionObject
{
public:
	StartButton(float i_x, float i_y, float i_width, float i_height
			,SlotState* i_slot_state)
		: x(i_x), y(i_y), width(i_width), height(i_height)
			, slotState(i_slot_state)
	{
		obj = std::unique_ptr<CanvasObject>(CanvasBgObjectFactory::create2DRect(x, y, -1.0, width, height));
	}

	/*virtual*/
	void on_click() override;

	/*virtual*/
	bool is_clicked(float xCoord, float yCoord) const override;

	/*virtual*/
	void draw() override;

private:
	float x, y;
	float width, height;

	SlotState * slotState;

	std::unique_ptr<CanvasObject> obj;
};


class Slot2DEngine : public SlotEngine
{
private:

	struct t_2Dslot_canvas_container
	{
		t_2Dslot_canvas_container(unsigned initWheel, unsigned initSlot, CanvasObject * initObj)
			: wheel {initWheel}, slot {initSlot}, obj {initObj}
		{}

		unsigned wheel;
		unsigned slot;
		std::unique_ptr<CanvasObject> obj;
	};


	using t_2Dslots = std::list<t_2Dslot_canvas_container>;


public:

	Slot2DEngine(unsigned initWheels, unsigned initSlots
					, CanvasObjectFactory* initSlotFactory);

	/*virtual*/
	void animate() override;

	/*virtual*/
	void render_scene() override;

	/*virtual*/
	void on_click(int button, int state, float x, float y) override;

private:

	CanvasObject* find_object(unsigned wheel, unsigned slot);

	void draw_wheel(unsigned wheel);

	void shiftSlot(unsigned wheel);

	bool del_canvas_object(unsigned fWheel, unsigned fSlot);

	bool update_canvas_object(unsigned oldWheel, unsigned oldSlot
								, unsigned newWheel, unsigned newSlot);

private:

	unsigned wheels;
	unsigned slots;

	t_2Dslots slotObjects;
	CanvasObjectFactory* slotFactory;

	std::list<std::unique_ptr<CanvasObject>> bgObjects;


	bool is_timePointInitialized {false};
	std::chrono::steady_clock::time_point timePrevCadr;

	std::unique_ptr<SlotState> slotState;
	std::unique_ptr<ActionObject> startButton;


	float 	  XstartPoint {-2.5f}
			, YstartPoint {-1.0f}
			, ZstartPoint {-1.0f};

	float 	  dXoffsetWheel {1.0f}
			, dYoffsetSlot	{1.0f};

	float slotWidth = 0.9f;
	float slotHeight = 0.9f;

};







