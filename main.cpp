/*
 * main.cpp
 *
 *  Created on: Sep 29, 2016
 *      Author: alex
 */


#include <memory>
#include <iostream>

#include <GL/glut.h>
#include <GL/gl.h>

#include "SOIL.h"

#include "openGLinit.hpp"
#include "CanvasObject.hpp"
#include "SlotEngine.hpp"
#include "CanvasObjectFactory.hpp"
#include "TexturePool.hpp"

SlotEngine *slotEngine;
TexturePool *slotTexturePool;
TexturePool *bgTexturePool;

const unsigned INITIAL_FPS = 60;


void display()
{
	if (slotEngine)
	{
		slotEngine->render_scene();
	}
}


void timer_func(int value)
{
	glutTimerFunc(1000/INITIAL_FPS, timer_func, 0);//1000/INITIAL_FPS

	if (slotEngine)
	{
		slotEngine->animate();
	}
}

void on_mouse_click(int button, int state, int x, int y)
{
	double calcX = ((double)x/glutGet(GLUT_WINDOW_WIDTH) - 0.5) * 2 * sceneWidth;
	double calcY = (0.5 - (double)y/glutGet(GLUT_WINDOW_HEIGHT)) * 2 * sceneHeight;

//	std::cout << "Mouse clicked with {button:" << button
//				<< " ,state:" << state
//				<< " ,x:" << x
//				<< " ,y:" << y
//				<< " ,w:" << glutGet(GLUT_WINDOW_WIDTH)
//				<< " ,h:" << glutGet(GLUT_WINDOW_HEIGHT)
//				<< " ,calcX:" << calcX
//				<< " , calcY:" << calcY
//				<< std::endl;

	slotEngine->on_click(button, state, calcX, calcY);
}


int main(int argc, char* argv[])
{
	openGLinit(argc, argv);


	slotTexturePool = new TextureSlots();
	bgTexturePool = new TextureBg();

	slotEngine =
		new Slot2DEngine(5,4, new TextureObjectFactory2D(slotTexturePool), bgTexturePool);


	glutDisplayFunc(display);

	glutMouseFunc(on_mouse_click);

	glutTimerFunc(0, timer_func, 0);

	glutMainLoop();

}
