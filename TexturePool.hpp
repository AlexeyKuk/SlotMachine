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


using t_texture_path = std::pair<std::string, std::string>;

const std::vector<t_texture_path> slotTexturePath=
	{
					{std::string("angry"), std::string("pic/angry.png")}
					,{std::string("chrome"), std::string("pic/chrome.png")}
					,{std::string("es"), std::string("pic/es.png")}
					,{std::string("linux"), std::string("pic/linux.png")}
					,{std::string("rad"), std::string("pic/rad.png")}
					,{std::string("smile"), std::string("pic/smile.png")}

	};


const std::vector<t_texture_path> bgTexturePath=
	{
					 {std::string("spin1"), std::string("/home/alex/eclipse_mars/SlotMachine/pic/spin1.png")}
					,{std::string("spin2"), std::string("/home/alex/eclipse_mars/SlotMachine/pic/spin2.png")}
	};

class TexturePool
{
public:

	virtual GLuint get_texture(std::string str) const = 0;
	virtual GLuint get_texture_by_id(unsigned id) const = 0;
	virtual unsigned get_count_of_texture() const = 0;

	virtual ~TexturePool() {}
};



class TexturePool2DSlot : public TexturePool
{
public:

	TexturePool2DSlot(const std::vector<t_texture_path>& i_pathToTexture)
		: pathToTexture(i_pathToTexture)
	{ load(); }

	/*virtual*/
	GLuint get_texture(std::string str) const override;

	/*virtual*/
	virtual GLuint get_texture_by_id(unsigned id) const override {return texture[id];}

	/*virtual*/
	unsigned get_count_of_texture() const override {return texture.size();}

private:

	void load();

private:
	std::vector<GLuint> texture;

	const std::vector<t_texture_path>& pathToTexture;
};


// Pool for slot's textures
class TextureSlots : public TexturePool2DSlot
{
public:
	TextureSlots()
		: TexturePool2DSlot(slotTexturePath)
	{}
};

// Pool for background textures
class TextureBg : public TexturePool2DSlot
{
public:
	TextureBg()
		: TexturePool2DSlot(bgTexturePath)
	{}
};



