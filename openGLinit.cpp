/*
 * openGLinit.cpp
 *
 *  Created on: Oct 3, 2016
 *      Author: alex
 */

#include "openGLinit.hpp"


void openGLinit(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL Tutorial");

	glutReshapeFunc(reshape2);
}

void onResize (int newWidth, int newHeight)
{
	if (newHeight==0) return;

	glViewport(0,0,newWidth,newHeight);

//	double aspect=double(newWidth)/newHeight;

	glOrtho(-sceneWidth, sceneWidth, -sceneHeight, sceneHeight, nearZ, farZ);

//	if (aspect > 1)
//		glOrtho(-sceneWidth/2*aspect, sceneWidth/2*aspect, -sceneHeight/2, sceneWidth/2, nearZ, farZ);
//		glOrtho(-sceneWidth/2*aspect, sceneWidth/2*aspect, -sceneHeight/2, sceneHeight/2, nearZ, farZ);
//	else
//		glOrtho(-sceneWidth/2, sceneWidth/2, -sceneHeight/2/aspect, sceneWidth/2/aspect, nearZ, farZ);
//		glOrtho(-sceneWidth/2, sceneWidth/2, -sceneHeight/2/aspect, sceneHeight/2/aspect, nearZ, farZ);
}



void reshape(int w, int h)
{
		glViewport(0, 0, w, h);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
//		gluOrtho2D(0, w, 0, h);
		gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
}



void reshape2 (int w, int h)
{
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
//	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,100.0f);
//	gluPerspective(40.0f,1.0f,0.1f,100.0f);

	onResize(w,h);

	glMatrixMode(GL_MODELVIEW);
}



//void loadTexure()
//{
//	GLuint texture_tmp;
//
//	texture_tmp = SOIL_load_OGL_texture(	"/home/alex/eclipse_mars/SlotMachine/train.png" //texturePath[i].second.c_str()
//										, SOIL_LOAD_RGBA
//										, SOIL_CREATE_NEW_ID
//										, SOIL_FLAG_INVERT_Y
//										);
//
//
//	glBindTexture(GL_TEXTURE_2D, texture_tmp);
//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//
//	glEnable(GL_TEXTURE_2D);
//
//	glBindTexture(GL_TEXTURE_2D, texture_tmp);
//
//	glLoadIdentity();
//	glTranslatef(XstartPoint, YstartPoint+3.0f, ZstartPoint);
//
//	glBegin(GL_QUADS);
//
//	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f,0.0f,0.0f);
//	glTexCoord2f(1.0f, 0.0f); glVertex3f(5.0f,0.0f,0.0f);
//	glTexCoord2f(1.0f, 1.0f); glVertex3f(5.0f,-5.0f,0.0f);
//	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f,-5.0f,0.0f);
//
//	glEnd();
//
//	glDisable(GL_TEXTURE_2D);


//	glPushMatrix();

//	glLoadIdentity();
//	glRasterPos3f(3.5f, -3.0f, 0.0f);
//	glTranslatef(3.5f, -3.0f, 0.0f);
//	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'A');

//	glPopMatrix();
//}



