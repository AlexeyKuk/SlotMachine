/*
 * openGLinit.cpp
 *
 *  Created on: Oct 3, 2016
 *      Author: alex
 */

#include "openGLinit.hpp"

#include "constants.hpp"


void openGLinit(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT);

	glutCreateWindow("SlotMachine");

	glutReshapeFunc(reshape);
}

void onResize (int newWidth, int newHeight)
{
	if (newHeight==0) return;

	glViewport(0,0,newWidth,newHeight);

	glOrtho(SCENE_HORIZ_MIN, SCENE_HORIZ_MAX, SCENE_VERT_MIN, SCENE_VERT_MAX, NEAREST_Z, FARTHEST_Z);
}


void reshape (int w, int h)
{
	glClearColor(BG_COLOR[0], BG_COLOR[1], BG_COLOR[2], BG_COLOR[3]);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glShadeModel(GL_SMOOTH);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	onResize(w,h);

	glMatrixMode(GL_MODELVIEW);
}

