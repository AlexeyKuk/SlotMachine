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

	glutInitWindowSize(CONFIG.get_INIT_WINDOW_WIDTH(), CONFIG.get_INIT_WINDOW_HEIGHT());

	glutCreateWindow("SlotMachine");

	glutReshapeFunc(reshape);
}

void onResize (int newWidth, int newHeight)
{
	if (newHeight==0) return;

	glViewport(0,0,newWidth,newHeight);

	glOrtho(CONFIG.get_SCENE_HORIZ_MIN(), CONFIG.get_SCENE_HORIZ_MAX()
			, CONFIG.get_SCENE_VERT_MIN(), CONFIG.get_SCENE_VERT_MAX()
			, CONFIG.get_NEAREST_Z(), CONFIG.get_FARTHEST_Z());
}


void reshape (int w, int h)
{
	float * p_BG_COLOR = CONFIG.get_BG_COLOR();
	glClearColor(p_BG_COLOR[0], p_BG_COLOR[1], p_BG_COLOR[2], p_BG_COLOR[3]);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glShadeModel(GL_SMOOTH);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	onResize(w,h);

	glMatrixMode(GL_MODELVIEW);
}

