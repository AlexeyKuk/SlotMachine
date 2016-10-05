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
#include "SlotState.hpp"
#include "FPScalc.hpp"
#include "constants.hpp"


class SlotEngine
{
public:

	virtual void render_scene() = 0;

	virtual void animate() = 0;

	virtual void on_click(int button, int state, float x, float y) = 0;

	virtual ~SlotEngine() {}
};





class Slot2DEngine : public SlotEngine
{
private:

	struct t_2Dslot_canvas_container
	{
		t_2Dslot_canvas_container(unsigned initWheel, unsigned initSlot, std::unique_ptr<CanvasObject>&& initObj)
			: wheel {initWheel}, slot {initSlot}, obj {std::move(initObj)}
		{}

		unsigned wheel;
		unsigned slot;
		std::unique_ptr<CanvasObject> obj;
	};


	using t_2Dslots = std::list<t_2Dslot_canvas_container>;


public:

	Slot2DEngine(unsigned initWheels, unsigned initSlots
					, CanvasObjectFactory* initSlotFactory
					, TexturePool * i_poolBgTexture);

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
	TexturePool * poolBgTexture;

	std::list<std::unique_ptr<CanvasObject>> bgObjects;


	bool is_timePointInitialized {false};
	std::chrono::steady_clock::time_point timePrevCadr;

	std::unique_ptr<SlotState> slotState;
	std::unique_ptr<ActionObject> startButton;
};







