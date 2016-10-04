/*
 * openGLinit.hpp
 *
 *  Created on: Oct 3, 2016
 *      Author: alex
 */

#pragma once

#include <GL/glut.h>


const double sceneWidth 			{ 3 };
const double sceneHeight 			{ 4 };
static const double nearZ 			{ 0.1 };
static const double farZ 			{ 100.0 };

void onResize (int newWidth, int newHeight);

void reshape(int w, int h);

void reshape2 (int w, int h);

void openGLinit(int argc, char* argv[]);
