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
	bgObjects.emplace_back(CanvasBgObjectFactory::create2DRect(   CONFIG.get_LEFT_SLOT_BORDER()
																, CONFIG.get_BOT_SLOT_BORDER() - CONFIG.get_OFFSET_SLOT()
																, CONFIG.get_Z_SLOT_COORDINATE()
																, CONFIG.get_COUNT_WHEELS() * CONFIG.get_OFFSET_WHEEL()
																, CONFIG.get_OFFSET_SLOT() )
							);
	bgObjects.emplace_back(CanvasBgObjectFactory::create2DRect(   CONFIG.get_LEFT_SLOT_BORDER()
																, CONFIG.get_BOT_SLOT_BORDER() + CONFIG.get_COUNT_SLOTS() * CONFIG.get_OFFSET_SLOT()
																, CONFIG.get_Z_SLOT_COORDINATE()
																, CONFIG.get_COUNT_WHEELS() * CONFIG.get_OFFSET_WHEEL()
																, CONFIG.get_OFFSET_SLOT() )
							);

	// create slot's state to set animation parameters
	slotState = std::unique_ptr<SlotState>(new SlotState(wheels));

	float * p_WHEEL_DELAYED	= CONFIG.get_WHEEL_DELAYED();
	float * p_WHEEL_SPEED	= CONFIG.get_WHEEL_SPEED();
	float * p_WHEEL_SLOWING	= CONFIG.get_WHEEL_SLOWING();

	slotState->set_delayed	(std::vector<float>(&p_WHEEL_DELAYED[0], &p_WHEEL_DELAYED[0] + wheels));
	slotState->set_speed	(std::vector<float>(&p_WHEEL_SPEED[0]  , &p_WHEEL_SPEED[0]   + wheels));
	slotState->set_slowing	(std::vector<float>(&p_WHEEL_SLOWING[0], &p_WHEEL_SLOWING[0] + wheels));


	// create a Start button
	CanvasObject * textureSpin1 = new TextureRectStaticObject(poolBgTexture->get_texture(CONFIG.get_START_BUTTON_TEXTURE_1())
																, CONFIG.get_START_BUTTON_LEFT()
																, CONFIG.get_START_BUTTON_BOT()
																, CONFIG.get_Z_SLOT_COORDINATE()
																, CONFIG.get_START_BUTTON_WIDTH()
																, CONFIG.get_START_BUTTON_HEIGHT() );

	CanvasObject * textureSpin2 = new TextureRectStaticObject(poolBgTexture->get_texture(CONFIG.get_START_BUTTON_TEXTURE_2())
																, CONFIG.get_START_BUTTON_LEFT()
																, CONFIG.get_START_BUTTON_BOT()
																, CONFIG.get_Z_SLOT_COORDINATE()
																, CONFIG.get_START_BUTTON_WIDTH()
																, CONFIG.get_START_BUTTON_HEIGHT());

	startButton = std::unique_ptr<ActionObject>
					(new StartButton(  CONFIG.get_START_BUTTON_LEFT()
									 , CONFIG.get_START_BUTTON_BOT()
									 , CONFIG.get_START_BUTTON_WIDTH()
									 , CONFIG.get_START_BUTTON_HEIGHT()
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

		glTranslatef( CONFIG.get_LEFT_SLOT_BORDER() + CONFIG.get_OFFSET_WHEEL() * wheel
					, CONFIG.get_BOT_SLOT_BORDER() - slotState->get_shift(wheel)
					, CONFIG.get_Z_SLOT_COORDINATE() );

		draw_wheel(wheel);
	}


	// draw BG objects
	float * p_BG_COLOR = CONFIG.get_BG_COLOR();
	glColor3f(p_BG_COLOR[0], p_BG_COLOR[1], p_BG_COLOR[2]);

	for (const auto& obj : bgObjects)
		obj->draw(0.0f, 0.0f); // width and height are unused

	float * p_ALL_COLORS = CONFIG.get_ALL_COLORS();
	glColor3f(p_ALL_COLORS[0], p_ALL_COLORS[1], p_ALL_COLORS[2]);


	startButton->draw();
}


void Slot2DEngine::draw_wheel(unsigned wheel)
{
	for (unsigned slot = 0; slot < slots; ++slot)
	{
		auto * obj = find_object(wheel, slot);
		if (obj != nullptr)
			obj->draw(CONFIG.get_SLOT_WIDTH(), CONFIG.get_SLOT_HEIGHT());

		glTranslatef(0.0f, CONFIG.get_OFFSET_WHEEL(), 0.0f);
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


