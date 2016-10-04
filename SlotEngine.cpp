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
	bgObjects.emplace_back(CanvasBgObjectFactory::create2DRect(XstartPoint, YstartPoint - 1.0f, ZstartPoint, 5.0f, 1.0f));
	bgObjects.emplace_back(CanvasBgObjectFactory::create2DRect(XstartPoint, YstartPoint + 3.0f, ZstartPoint, 5.0f, 1.0f));

	// draw "Start" button
	bgObjects.emplace_back(CanvasBgObjectFactory::create2DRect(XstartPoint, YstartPoint - 2.0f, ZstartPoint, 1.0f, 0.3f));

	// create slots state to set animation's parameters
	slotState = std::unique_ptr<SlotState>(new SlotState(wheels));

	// customize slotState (max for 5 wheels)
	std::vector<float> delayed 	{0.4f, 0.8f, 1.2f, 1.4f, 1.8f};
	std::vector<float> speed 	{5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
//	std::vector<float> speed 	(5, 5.0f);
	std::vector<float> slowing 	(5, 8.0f);//{0.8f, 0.7f, 0.6f, 0.5f, 0.4f};

	for (auto & e : delayed) e *= 3.0f;

	slotState->set_delayed	(std::vector<float>(delayed.begin(), delayed.begin() + wheels));
	slotState->set_speed	(std::vector<float>(speed.begin(), speed.begin() + wheels));
	slotState->set_slowing	(std::vector<float>(slowing.begin(), slowing.begin() + wheels));

	// create a Start button
	CanvasObject * tmp1 = new TextureRectStaticObject(poolBgTexture->get_texture("spin1"), 1.5f, -2.5f, -1.0f, 1.0f, 0.5f);
	CanvasObject * tmp2 = new TextureRectStaticObject(poolBgTexture->get_texture("spin2"), 1.5f, -2.5f, -1.0f, 1.0f, 0.5f);

	startButton = std::unique_ptr<ActionObject>
					(new StartButton(1.5f, -2.5f, 1.0f, 0.5f, slotState.get(), tmp1, tmp2));
}


void Slot2DEngine::on_click(int button, int state, float x, float y)
{
	if (startButton->is_clicked(x, y))
		startButton->on_click();
}


void Slot2DEngine::render_scene()
{
	glClear(GL_COLOR_BUFFER_BIT); //| GL_DEPTH_BUFFER_BIT);

	for (unsigned wheel = 0; wheel < wheels; ++wheel)
	{
		glLoadIdentity();

		glTranslatef(XstartPoint + dXoffsetWheel * wheel, YstartPoint - slotState->get_shift(wheel), ZstartPoint);

		draw_wheel(wheel);
	}


	// draw BG objects
	glColor3f(0.1f,0.1f,0.1f);

	for (const auto& obj : bgObjects)
		obj->draw(0.0f, 0.0f); // width and height are unused

	glColor3f(1.0f,1.0f,1.0f);


	startButton->draw();

	// draw PFS
	std::string str("fps = ");
	str += std::to_string(fps.get_fps());

	glLoadIdentity();
	glRasterPos3f(XstartPoint, YstartPoint-2.8f, ZstartPoint);

	for (auto e : str)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, e);
	}

	glutSwapBuffers();
}


void Slot2DEngine::draw_wheel(unsigned wheel)
{
	for (unsigned slot = 0; slot < slots; ++slot)
	{
		auto * obj = find_object(wheel, slot);
		if (obj != nullptr)
			obj->draw(slotWidth, slotHeight);

		glTranslatef(0.0f, dYoffsetSlot, 0.0f);
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

	fps.add_cadr(duration.count());

	auto isNeedNextSlot = slotState->turn(duration.count());
	for (size_t i = 0; i < isNeedNextSlot.size(); ++i)
	{
		if (isNeedNextSlot[i])
			shiftSlot(i);
	}

	timePrevCadr = t2;

	render_scene();
}


