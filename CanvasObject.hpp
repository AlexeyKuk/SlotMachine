
#pragma once

#include <GL/glut.h>


/*
 * CanvasObject
 * 			Pure virtual base class to draw an object
 */
class CanvasObject
{

public:

	virtual void draw(float width, float height) const = 0;

	virtual ~CanvasObject() {}
};


/*
 * CanvasRectObject
 * 			Draw rectangle from current position with specified width and height
 * 			without any textures and has not any offsets or coordinates.
 */
class CanvasRectObject : public CanvasObject
{
public:

	/*virtual*/
	void draw(float width, float height) const override;

};


/*
 * CanvasStaticRectObject
 * 			Draw a rectangle in specified position (x,y,z)
 * 			and rectWidth, rectHeight are specified in creation.
 *
 */
class CanvasStaticRectObject : public CanvasObject
{
public:
	CanvasStaticRectObject(float x, float y, float z, float width, float height)
		: coord3f {x, y, z}, rectWidth {width}, rectHeight {height}
	{}


	// params width & height will be ignored
	/*virtual*/
	void draw(float width, float height) const override;

private:

	// Offset from Identity position
	float coord3f[3];

	float rectWidth;
	float rectHeight;
};



/*
 * TextureRectObject
 *			Draw a texture mapped on rectangle is specified by width and height
 *			and current position.
 *			Have a handle to loaded texture.
 */
class TextureRectObject : public CanvasRectObject
{
public:

	TextureRectObject(GLuint initTexture)
		: texture(initTexture)
	{}

	/*virtual*/
	void draw(float width, float height) const override;

private:
	GLuint texture;
};
