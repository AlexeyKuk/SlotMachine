
#pragma once

#include <memory>

#include "CanvasObject.hpp"
#include "TexturePool.hpp"


/*
 * CanvasObjectFactory
 * 		Pure virtual class for Abstract Factory to create next slot element
 */
class CanvasObjectFactory
{
public:
	virtual std::unique_ptr<CanvasObject> create(unsigned weel, unsigned slot) = 0;

	virtual ~CanvasObjectFactory() {};
};


class CanvasBgObjectFactory
{
public:
	static CanvasObject* create2DRect(float x, float y, float z, float width, float height);
};


/*
 * CanvasObjectFactory2D
 * 		Create next slot element for 2D Slot Machine
 */
class CanvasObjectFactory2D : public CanvasObjectFactory
{
public:
	/*virtual*/
	std::unique_ptr<CanvasObject> create(unsigned weel, unsigned slot) override;

};


/*
 * TextureObjectFactory2D
 * 			Create next slot element with loaded texture (from texturePool)
 */
class TextureObjectFactory2D : public CanvasObjectFactory
{
public:
	TextureObjectFactory2D(TexturePool * initTexturePool)
		: texturePool{initTexturePool}
	{}

	/*virtual*/
	std::unique_ptr<CanvasObject> create(unsigned weel, unsigned slot) override;

private:

	TexturePool * texturePool;
};


