/*
 * TexturePool.hpp
 *
 *  Created on: Sep 30, 2016
 *      Author: alex
 */

#pragma once

#include <string>
#include <utility>
#include <vector>

#include <GL/glut.h>


class TexturePool
{
public:

	virtual GLuint get_texture(std::string str) const = 0;
	virtual GLuint get_texture_by_id(unsigned id) const = 0;
	virtual unsigned get_count_of_texture() const = 0;

	virtual ~TexturePool() {}

private:

	virtual void load() = 0;
};




class TexturePool2DSlot : public TexturePool
{
public:

	TexturePool2DSlot() { load(); }

	/*virtual*/
	GLuint get_texture(std::string str) const override;

	/*virtual*/
	virtual GLuint get_texture_by_id(unsigned id) const override {return texture[id];}

	/*virtual*/
	unsigned get_count_of_texture() const {return countTexture;}

private:
	/*virtual*/
	void load() override;


	size_t	countTexture {0};
	std::vector<GLuint> texture;
};



