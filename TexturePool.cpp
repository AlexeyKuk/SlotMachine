/*
 * TexturePool.cpp
 *
 *  Created on: Sep 30, 2016
 *      Author: alex
 */

#include "SOIL.h"

#include "TexturePool.hpp"

#include <iostream>

using t_texture_path = std::pair<std::string, std::string>;

static std::vector<t_texture_path> texturePath=
	{
//					{std::string("logo"), std::string("/home/alex/eclipse_mars/SlotMachine/Debug/NeHe.bmp")}
					{std::string("angry"), std::string("/home/alex/eclipse_mars/SlotMachine/pic/angry.png")}
					,{std::string("chrome"), std::string("/home/alex/eclipse_mars/SlotMachine/pic/chrome.png")}
					,{std::string("es"), std::string("/home/alex/eclipse_mars/SlotMachine/pic/es.png")}
					,{std::string("linux"), std::string("/home/alex/eclipse_mars/SlotMachine/pic/linux.png")}
					,{std::string("rad"), std::string("/home/alex/eclipse_mars/SlotMachine/pic/rad.png")}
					,{std::string("smile"), std::string("/home/alex/eclipse_mars/SlotMachine/pic/smile.png")}

	};



void TexturePool2DSlot::load()
{
	countTexture = texturePath.size();
	texture.resize(countTexture);

	for (size_t i = 0; i < countTexture; ++i)
	{
		texture[i] = SOIL_load_OGL_texture(	texturePath[i].second.c_str()
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
	for (size_t i = 0; i < countTexture; ++i)
	{
		if (str == texturePath[i].first)
		{
			return texture[i];
		}
	}

	return 0;
}
