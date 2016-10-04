/*
 * CanvasObjectFactory.cpp
 *
 *  Created on: Sep 29, 2016
 *      Author: alex
 */

#include <random>

#include "CanvasObjectFactory.hpp"


std::unique_ptr<CanvasObject> CanvasObjectFactory2D::create(unsigned weel, unsigned slot)
{

	// TODO : need any logic
	return std::unique_ptr<CanvasObject>(new CanvasRectObject());
}


std::unique_ptr<CanvasObject> TextureObjectFactory2D::create(unsigned weel, unsigned slot)
{

	// TODO : need any logic

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, texturePool->get_count_of_texture()-1);

	GLuint text = texturePool->get_texture_by_id(dis(gen));

	return std::unique_ptr<CanvasObject>(new TextureRectObject(text));
}



CanvasObject* CanvasBgObjectFactory::create2DRect(float x, float y, float z, float width, float height)
{
	return new CanvasStaticRectObject(x, y, z, width, height);
}
