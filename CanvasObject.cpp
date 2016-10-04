/*
 * CanvasObject.cpp
 *
 *  Created on: Sep 29, 2016
 *      Author: alex
 */

#include <GL/glut.h>

#include "CanvasObject.hpp"


void CanvasRectObject::draw(float width, float height) const
{
	glBegin(GL_QUADS);

	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(width,0.0f,0.0f);
	glVertex3f(width,height,0.0f);
	glVertex3f(0.0f,height,0.0f);

	glEnd();
}


void CanvasStaticRectObject::draw(float width, float height) const
{
	glLoadIdentity();

	glTranslatef(coord3f[0], coord3f[1], coord3f[2]);

	glBegin(GL_QUADS);

	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(rectWidth,0.0f,0.0f);
	glVertex3f(rectWidth,rectHeight,0.0f);
	glVertex3f(0.0f,rectHeight,0.0f);

	glEnd();
}


void TextureRectObject::draw(float width, float height) const
{
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f,0.0f,0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(width,0.0f,0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(width,height,0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f,height,0.0f);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}

