/*
 * constants.hpp
 *
 *  Created on: Oct 5, 2016
 *      Author: alex
 */

#pragma once


// TODO : should be read from XML

const unsigned INITIAL_FPS 	= 60;

/*
 * 		OpenGL init params
 */

const double SCENE_HORIZ_MIN 	= -3.0;
const double SCENE_HORIZ_MAX 	=  3.0;
const double SCENE_VERT_MIN 	= -4.0;
const double SCENE_VERT_MAX 	=  4.0;

const double NEAREST_Z 		= 0.1;
const double FARTHEST_Z 	= 100.0;

const unsigned INIT_WINDOW_WIDTH 	= 800;
const unsigned INIT_WINDOW_HEIGHT 	= 600;

const float BG_COLOR[] = {0.1f, 0.1f, 0.1f, 0.0f};
const float ALL_COLORS[] = {1.0f, 1.0f, 1.0f, 0.0f};


/*
 * 		Slot machine parameters
 */

const unsigned COUNT_WHEELS = 5;
const unsigned COUNT_SLOTS	= 3;

// left bottom point of slots
const float LEFT_SLOT_BORDER	= -2.5f;
const float BOT_SLOT_BORDER		= -1.0f;
const float Z_SLOT_COORDINATE	= -1.0f;

// wheel's and slot's height and width
const float SLOT_WIDTH		= 0.9f;
const float SLOT_HEIGHT		= 0.9f;
const float WHEEL_WIDTH		= 0.9f;
const float WHEEL_HEIGHT	= 0.9f;

// offset between wheels and slots
const float OFFSET_WHEEL		= 1.0f;
const float OFFSET_SLOT			= 1.0f;

// Start button parameters
const float START_BUTTON_LEFT	=  1.5f;
const float START_BUTTON_BOT	= -2.5f;
const float START_BUTTON_WIDTH	=  1.0f;
const float START_BUTTON_HEIGHT	=  0.5f;

const char * const START_BUTTON_TEXTURE_1 = "spin1";
const char * const START_BUTTON_TEXTURE_2 = "spin2";


/*
 * 		Slot dynamic parameters
 */
const float WHEEL_DELAYED[] = {0.4f, 0.8f, 1.2f, 1.4f, 1.8f, 2.2f, 2.6f, 3.0f, 3.4f, 3.8f};
const float WHEEL_SLOWING[] = {8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f};
const float WHEEL_SPEED[] 	= {5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};

static_assert(sizeof(WHEEL_DELAYED)/sizeof(WHEEL_DELAYED[0]) >= COUNT_WHEELS
		, "size of WHEEL_DELAYED should not less than COUNT_WHEELS");

static_assert(sizeof(WHEEL_SLOWING)/sizeof(WHEEL_SLOWING[0]) >= COUNT_WHEELS
		, "size of WHEEL_SLOWING should not less than COUNT_WHEELS");

static_assert(sizeof(WHEEL_SPEED)/sizeof(WHEEL_SPEED[0]) >= COUNT_WHEELS
		, "size of WHEEL_SPEED should not less than COUNT_WHEELS");




/*
 * 	FPS draw
 */
const float DRAW_FPS_POS[] = {-2.5f, -3.8f, -1.0f};



