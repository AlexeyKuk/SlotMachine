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
#include "FPScalc.hpp"
#include "constants.hpp"


// GLOBAL objects
SlotEngine 	* slotEngine		{nullptr};
TexturePool * slotTexturePool	{nullptr};
TexturePool * bgTexturePool		{nullptr};
FPScalc		* fps				{nullptr};

CanvasObjectFactory * slotObjectFactory {nullptr};

void init_global_objects()
{
	fps = new FPScalc();

	slotTexturePool 	= new TextureSlots();
	bgTexturePool 		= new TextureBg();
	slotObjectFactory 	= new TextureObjectFactory2D(slotTexturePool);

	slotEngine =
		new Slot2DEngine( COUNT_WHEELS, COUNT_SLOTS + 1 // +1 for hidden slot on the top
						, slotObjectFactory
						, bgTexturePool );

}

void display();

void timer_func(int value);

void on_mouse_click(int button, int state, int x, int y);


/*
 * 	MAIN function
 */
int main(int argc, char* argv[])
{
	openGLinit(argc, argv);

	init_global_objects();

	glutDisplayFunc(display);

	glutMouseFunc(on_mouse_click);

	// rise the timer
	glutTimerFunc(0, timer_func, 0);

	glutMainLoop();

}//end main()


/*
 *		Functions process events
 */


void display()
{
	// fps calc
	if (fps)
		fps->add_cadr();

	// start to render scene
	glClear(GL_COLOR_BUFFER_BIT);

	if (slotEngine)
		slotEngine->animate();

	// draw fps on the screen
	if (fps)
		DrawFPS::draw(*fps);

	// stop render and swap buffers
	glutSwapBuffers();
}


void timer_func(int value)
{
	// rise timer to next screen update
	glutTimerFunc(1000/INITIAL_FPS, timer_func, 0);

	display();
}


void on_mouse_click(int button, int state, int x, int y)
{
	double calcX = ((double)x/glutGet(GLUT_WINDOW_WIDTH)) * (SCENE_HORIZ_MAX - SCENE_HORIZ_MIN) + SCENE_HORIZ_MIN;
	double calcY = (1.0 - (double)y/glutGet(GLUT_WINDOW_HEIGHT)) * (SCENE_VERT_MAX - SCENE_VERT_MIN) + SCENE_VERT_MIN;

	if (slotEngine)
		slotEngine->on_click(button, state, calcX, calcY);
}


