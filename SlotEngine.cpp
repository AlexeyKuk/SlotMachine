/*
 * SlotEngine.cpp
 *
 *  Created on: Sep 29, 2016
 *      Author: alex
 */

#include <iostream>
#include <cmath>
#include <string>

#include <GL/glut.h>

#include "SOIL.h"

#include "SlotEngine.hpp"



Slot2DEngine::Slot2DEngine(unsigned initWheels, unsigned initSlots
							, CanvasObjectFactory* initSlotFactory
							, TexturePool * i_poolBgTexture)
	: wheels(initWheels)
	 ,slots(initSlots)
	 ,slotFactory(initSlotFactory)
	 ,poolBgTexture(i_poolBgTexture)
{

	// Add initial slot's objects created by slotFactory
	// slotObjects is a container with:
	//		(wheel, slot) - position on the machine
	// 		obj - unique pointer to created canvas object
	for (unsigned wheel = 0; wheel < wheels; ++wheel)
	{
		for (unsigned slot = 0; slot < slots; ++slot)
		{
			slotObjects.emplace_back(  wheel
									 , slot
									 , slotFactory->create(wheel, slot)
								);
		}
	}

	// Create background objects to hide regions on top and bottom for creating wheels animation.
	bgObjects.emplace_back(CanvasBgObjectFactory::create2DRect(   LEFT_SLOT_BORDER
																, BOT_SLOT_BORDER - OFFSET_SLOT
																, Z_SLOT_COORDINATE
																, COUNT_WHEELS * OFFSET_WHEEL
																, OFFSET_SLOT )
							);
	bgObjects.emplace_back(CanvasBgObjectFactory::create2DRect(   LEFT_SLOT_BORDER
																, BOT_SLOT_BORDER + COUNT_SLOTS * OFFSET_SLOT
																, Z_SLOT_COORDINATE
																, COUNT_WHEELS * OFFSET_WHEEL
																, OFFSET_SLOT )
							);

	// create slot's state to set animation parameters
	slotState = std::unique_ptr<SlotState>(new SlotState(wheels));

	slotState->set_delayed	(std::vector<float>(&WHEEL_DELAYED[0], &WHEEL_DELAYED[0] + wheels));
	slotState->set_speed	(std::vector<float>(&WHEEL_SPEED[0]  , &WHEEL_SPEED[0]   + wheels));
	slotState->set_slowing	(std::vector<float>(&WHEEL_SLOWING[0], &WHEEL_SLOWING[0] + wheels));


	// create a Start button
	CanvasObject * textureSpin1 = new TextureRectStaticObject(poolBgTexture->get_texture(START_BUTTON_TEXTURE_1)
																, START_BUTTON_LEFT
																, START_BUTTON_BOT
																, Z_SLOT_COORDINATE
																, START_BUTTON_WIDTH
																, START_BUTTON_HEIGHT);

	CanvasObject * textureSpin2 = new TextureRectStaticObject(poolBgTexture->get_texture(START_BUTTON_TEXTURE_2)
																, START_BUTTON_LEFT
																, START_BUTTON_BOT
																, Z_SLOT_COORDINATE
																, START_BUTTON_WIDTH
																, START_BUTTON_HEIGHT);

	startButton = std::unique_ptr<ActionObject>
					(new StartButton(  START_BUTTON_LEFT
									 , START_BUTTON_BOT
									 , START_BUTTON_WIDTH
									 , START_BUTTON_HEIGHT
									 , slotState.get()
									 , textureSpin1, textureSpin2)
					);
}


void Slot2DEngine::on_click(int button, int state, float x, float y)
{
	if (startButton->is_clicked(x, y))
		startButton->on_click();
}


void Slot2DEngine::render_scene()
{

	for (unsigned wheel = 0; wheel < wheels; ++wheel)
	{
		glLoadIdentity();

		glTranslatef( LEFT_SLOT_BORDER + OFFSET_WHEEL * wheel
					, BOT_SLOT_BORDER - slotState->get_shift(wheel)
					, Z_SLOT_COORDINATE );

		draw_wheel(wheel);
	}


	// draw BG objects
	glColor3f(BG_COLOR[0], BG_COLOR[1], BG_COLOR[2]);

	for (const auto& obj : bgObjects)
		obj->draw(0.0f, 0.0f); // width and height are unused

	glColor3f(ALL_COLORS[0], ALL_COLORS[1], ALL_COLORS[2]);


	startButton->draw();
}


void Slot2DEngine::draw_wheel(unsigned wheel)
{
	for (unsigned slot = 0; slot < slots; ++slot)
	{
		auto * obj = find_object(wheel, slot);
		if (obj != nullptr)
			obj->draw(SLOT_WIDTH, SLOT_HEIGHT);

		glTranslatef(0.0f, OFFSET_WHEEL, 0.0f);
	}
}



CanvasObject* Slot2DEngine::find_object(unsigned wheel, unsigned slot)
{
	for(const auto & canvasObj : slotObjects)
	{
		if (canvasObj.wheel == wheel && canvasObj.slot == slot)
			return canvasObj.obj.get();
	}

	return nullptr;
}


bool Slot2DEngine::del_canvas_object(unsigned fWheel, unsigned fSlot)
{
	for (auto it = slotObjects.begin(); it != slotObjects.end(); ++it)
	{
		if ((*it).wheel == fWheel && (*it).slot == fSlot)
		{
			slotObjects.erase(it);
			return true;
		}
	}

	return false;
}

bool Slot2DEngine::update_canvas_object(unsigned oldWheel, unsigned oldSlot
							, unsigned newWheel, unsigned newSlot)
{
	for(auto & canvasObj : slotObjects)
	{
		if (canvasObj.wheel == oldWheel && canvasObj.slot == oldSlot)
		{
			canvasObj.wheel = newWheel;
			canvasObj.slot = newSlot;
			return true;
		}
	}

	return false;
}


void Slot2DEngine::shiftSlot(unsigned wheel)
{
	del_canvas_object(wheel, 0);

	for (size_t i = 0; i < slots-1; ++i)
	{
		update_canvas_object(wheel, i+1, wheel, i);
	}


	slotObjects.emplace_back(wheel, slots-1, slotFactory->create(wheel, slots-1));
}


void Slot2DEngine::animate()
{
	if (!is_timePointInitialized)
	{
		timePrevCadr = std::chrono::steady_clock::now();
		is_timePointInitialized = true;
		return;
	}

	std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();

	std::chrono::duration<double> duration =
			std::chrono::duration_cast<std::chrono::duration<double>>(t2 - timePrevCadr);


	auto isNeedNextSlot = slotState->turn(duration.count());
	for (size_t i = 0; i < isNeedNextSlot.size(); ++i)
	{
		if (isNeedNextSlot[i])
			shiftSlot(i);
	}

	timePrevCadr = t2;

	render_scene();
}


