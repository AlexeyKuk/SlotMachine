/*
 * TexturePool.cpp
 *
 *  Created on: Sep 30, 2016
 *      Author: alex
 */

#include "SOIL.h"

#include "TexturePool.hpp"

#include <iostream>

//using t_texture_path = std::pair<std::string, std::string>;


void TexturePool2DSlot::load()
{
	texture.resize(pathToTexture.size());

	for (size_t i = 0; i < texture.size(); ++i)
	{
		texture[i] = SOIL_load_OGL_texture(	pathToTexture[i].second.c_str()
											, SOIL_LOAD_AUTO
											, SOIL_CREATE_NEW_ID
											, SOIL_FLAG_INVERT_Y
											);

		glBindTexture(GL_TEXTURE_2D, texture[i]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}
}


GLuint TexturePool2DSlot::get_texture(std::string str) const
{
	for (size_t i = 0; i < texture.size(); ++i)
	{
		if (str == pathToTexture[i].first)
		{
			return texture[i];
		}
	}

	return 0;
}



