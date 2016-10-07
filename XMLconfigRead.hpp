/*
 * XMLconfigRead.hpp
 *
 *  Created on: Oct 7, 2016
 *      Author: alex
 */

#pragma once

#include <tuple>
#include <vector>
#include <string>

#include "XMLreader.hpp"

namespace xml_config_read
{

enum
{
		INITIAL_FPS
	,	SCENE_HORIZ_MIN
	,	SCENE_HORIZ_MAX
	,	SCENE_VERT_MIN
	,	SCENE_VERT_MAX
	,	NEAREST_Z
	,	FARTHEST_Z
	,	INIT_WINDOW_WIDTH
	,	INIT_WINDOW_HEIGHT
	,	BG_COLOR
	,	ALL_COLORS
	,	COUNT_WHEELS
	,	COUNT_SLOTS
	,	LEFT_SLOT_BORDER
	,	BOT_SLOT_BORDER
	,	Z_SLOT_COORDINATE
	,	SLOT_WIDTH
	,	SLOT_HEIGHT
	,	WHEEL_WIDTH
	,	WHEEL_HEIGHT
	,	OFFSET_WHEEL
	,	OFFSET_SLOT
	,	START_BUTTON_LEFT
	,	START_BUTTON_BOT
	,	START_BUTTON_WIDTH
	,	START_BUTTON_HEIGHT
	,	WHEEL_DELAYED
	,	WHEEL_SLOWING
	,	WHEEL_SPEED
	,	DRAW_FPS_POS
	,	START_BUTTON_TEXTURE_1
	,	START_BUTTON_TEXTURE_2

	, LAST_ELEM
};

const std::vector<const char*> paramNames
{
	"INITIAL_FPS"
	,"SCENE_HORIZ_MIN"
	,"SCENE_HORIZ_MAX"
	,"SCENE_VERT_MIN"
	,"SCENE_VERT_MAX"
	,"NEAREST_Z"
	,"FARTHEST_Z"
	,"INIT_WINDOW_WIDTH"
	,"INIT_WINDOW_HEIGHT"
	,"BG_COLOR"
	,"ALL_COLORS"
	,"COUNT_WHEELS"
	,"COUNT_SLOTS"
	,"LEFT_SLOT_BORDER"
	,"BOT_SLOT_BORDER"
	,"Z_SLOT_COORDINATE"
	,"SLOT_WIDTH"
	,"SLOT_HEIGHT"
	,"WHEEL_WIDTH"
	,"WHEEL_HEIGHT"
	,"OFFSET_WHEEL"
	,"OFFSET_SLOT"
	,"START_BUTTON_LEFT"
	,"START_BUTTON_BOT"
	,"START_BUTTON_WIDTH"
	,"START_BUTTON_HEIGHT"
	,"WHEEL_DELAYED"
	,"WHEEL_SLOWING"
	,"WHEEL_SPEED"
	,"DRAW_FPS_POS"
	,"START_BUTTON_TEXTURE_1"
	,"START_BUTTON_TEXTURE_2"
};

class XMLconfigRead
{
public:

	XMLconfigRead()
	{
//		std::get<INITIAL_FPS>(allParams)= read_elem_from_xml<std::tuple_element<INITIAL_FPS, decltype(allParams)>::type>(paramNames[INITIAL_FPS]);
		std::get<	INITIAL_FPS	>(allParams)= read_elem_from_xml<std::tuple_element<	INITIAL_FPS	, decltype(allParams)>::type>(paramNames[	INITIAL_FPS	]);
		std::get<	SCENE_HORIZ_MIN	>(allParams)= read_elem_from_xml<std::tuple_element<	SCENE_HORIZ_MIN	, decltype(allParams)>::type>(paramNames[	SCENE_HORIZ_MIN	]);
		std::get<	SCENE_HORIZ_MAX	>(allParams)= read_elem_from_xml<std::tuple_element<	SCENE_HORIZ_MAX	, decltype(allParams)>::type>(paramNames[	SCENE_HORIZ_MAX	]);
		std::get<	SCENE_VERT_MIN	>(allParams)= read_elem_from_xml<std::tuple_element<	SCENE_VERT_MIN	, decltype(allParams)>::type>(paramNames[	SCENE_VERT_MIN	]);
		std::get<	SCENE_VERT_MAX	>(allParams)= read_elem_from_xml<std::tuple_element<	SCENE_VERT_MAX	, decltype(allParams)>::type>(paramNames[	SCENE_VERT_MAX	]);
		std::get<	NEAREST_Z	>(allParams)= read_elem_from_xml<std::tuple_element<	NEAREST_Z	, decltype(allParams)>::type>(paramNames[	NEAREST_Z	]);
		std::get<	FARTHEST_Z	>(allParams)= read_elem_from_xml<std::tuple_element<	FARTHEST_Z	, decltype(allParams)>::type>(paramNames[	FARTHEST_Z	]);
		std::get<	INIT_WINDOW_WIDTH	>(allParams)= read_elem_from_xml<std::tuple_element<	INIT_WINDOW_WIDTH	, decltype(allParams)>::type>(paramNames[	INIT_WINDOW_WIDTH	]);
		std::get<	INIT_WINDOW_HEIGHT	>(allParams)= read_elem_from_xml<std::tuple_element<	INIT_WINDOW_HEIGHT	, decltype(allParams)>::type>(paramNames[	INIT_WINDOW_HEIGHT	]);
		std::get<	BG_COLOR	>(allParams)= read_elem_from_xml<std::tuple_element<	BG_COLOR	, decltype(allParams)>::type>(paramNames[	BG_COLOR	]);
		std::get<	ALL_COLORS	>(allParams)= read_elem_from_xml<std::tuple_element<	ALL_COLORS	, decltype(allParams)>::type>(paramNames[	ALL_COLORS	]);
		std::get<	COUNT_WHEELS	>(allParams)= read_elem_from_xml<std::tuple_element<	COUNT_WHEELS	, decltype(allParams)>::type>(paramNames[	COUNT_WHEELS	]);
		std::get<	COUNT_SLOTS	>(allParams)= read_elem_from_xml<std::tuple_element<	COUNT_SLOTS	, decltype(allParams)>::type>(paramNames[	COUNT_SLOTS	]);
		std::get<	LEFT_SLOT_BORDER	>(allParams)= read_elem_from_xml<std::tuple_element<	LEFT_SLOT_BORDER	, decltype(allParams)>::type>(paramNames[	LEFT_SLOT_BORDER	]);
		std::get<	BOT_SLOT_BORDER	>(allParams)= read_elem_from_xml<std::tuple_element<	BOT_SLOT_BORDER	, decltype(allParams)>::type>(paramNames[	BOT_SLOT_BORDER	]);
		std::get<	Z_SLOT_COORDINATE	>(allParams)= read_elem_from_xml<std::tuple_element<	Z_SLOT_COORDINATE	, decltype(allParams)>::type>(paramNames[	Z_SLOT_COORDINATE	]);
		std::get<	SLOT_WIDTH	>(allParams)= read_elem_from_xml<std::tuple_element<	SLOT_WIDTH	, decltype(allParams)>::type>(paramNames[	SLOT_WIDTH	]);
		std::get<	SLOT_HEIGHT	>(allParams)= read_elem_from_xml<std::tuple_element<	SLOT_HEIGHT	, decltype(allParams)>::type>(paramNames[	SLOT_HEIGHT	]);
		std::get<	WHEEL_WIDTH	>(allParams)= read_elem_from_xml<std::tuple_element<	WHEEL_WIDTH	, decltype(allParams)>::type>(paramNames[	WHEEL_WIDTH	]);
		std::get<	WHEEL_HEIGHT	>(allParams)= read_elem_from_xml<std::tuple_element<	WHEEL_HEIGHT	, decltype(allParams)>::type>(paramNames[	WHEEL_HEIGHT	]);
		std::get<	OFFSET_WHEEL	>(allParams)= read_elem_from_xml<std::tuple_element<	OFFSET_WHEEL	, decltype(allParams)>::type>(paramNames[	OFFSET_WHEEL	]);
		std::get<	OFFSET_SLOT	>(allParams)= read_elem_from_xml<std::tuple_element<	OFFSET_SLOT	, decltype(allParams)>::type>(paramNames[	OFFSET_SLOT	]);
		std::get<	START_BUTTON_LEFT	>(allParams)= read_elem_from_xml<std::tuple_element<	START_BUTTON_LEFT	, decltype(allParams)>::type>(paramNames[	START_BUTTON_LEFT	]);
		std::get<	START_BUTTON_BOT	>(allParams)= read_elem_from_xml<std::tuple_element<	START_BUTTON_BOT	, decltype(allParams)>::type>(paramNames[	START_BUTTON_BOT	]);
		std::get<	START_BUTTON_WIDTH	>(allParams)= read_elem_from_xml<std::tuple_element<	START_BUTTON_WIDTH	, decltype(allParams)>::type>(paramNames[	START_BUTTON_WIDTH	]);
		std::get<	START_BUTTON_HEIGHT	>(allParams)= read_elem_from_xml<std::tuple_element<	START_BUTTON_HEIGHT	, decltype(allParams)>::type>(paramNames[	START_BUTTON_HEIGHT	]);
		std::get<	WHEEL_DELAYED	>(allParams)= read_elem_from_xml<std::tuple_element<	WHEEL_DELAYED	, decltype(allParams)>::type>(paramNames[	WHEEL_DELAYED	]);
		std::get<	WHEEL_SLOWING	>(allParams)= read_elem_from_xml<std::tuple_element<	WHEEL_SLOWING	, decltype(allParams)>::type>(paramNames[	WHEEL_SLOWING	]);
		std::get<	WHEEL_SPEED	>(allParams)= read_elem_from_xml<std::tuple_element<	WHEEL_SPEED	, decltype(allParams)>::type>(paramNames[	WHEEL_SPEED	]);
		std::get<	DRAW_FPS_POS	>(allParams)= read_elem_from_xml<std::tuple_element<	DRAW_FPS_POS	, decltype(allParams)>::type>(paramNames[	DRAW_FPS_POS	]);
		std::get<	START_BUTTON_TEXTURE_1	>(allParams)= read_elem_from_xml<std::tuple_element<	START_BUTTON_TEXTURE_1	, decltype(allParams)>::type>(paramNames[	START_BUTTON_TEXTURE_1	]);
		std::get<	START_BUTTON_TEXTURE_2	>(allParams)= read_elem_from_xml<std::tuple_element<	START_BUTTON_TEXTURE_2	, decltype(allParams)>::type>(paramNames[	START_BUTTON_TEXTURE_2	]);

	}




	unsigned		get_INITIAL_FPS	()	{ return 	std::get	<	INITIAL_FPS	>	(allParams);	}
	float		get_SCENE_HORIZ_MIN	()	{ return 	std::get	<	SCENE_HORIZ_MIN	>	(allParams);	}
	float		get_SCENE_HORIZ_MAX	()	{ return 	std::get	<	SCENE_HORIZ_MAX	>	(allParams);	}
	float		get_SCENE_VERT_MIN	()	{ return 	std::get	<	SCENE_VERT_MIN	>	(allParams);	}
	float		get_SCENE_VERT_MAX	()	{ return 	std::get	<	SCENE_VERT_MAX	>	(allParams);	}
	float		get_NEAREST_Z	()	{ return 	std::get	<	NEAREST_Z	>	(allParams);	}
	float		get_FARTHEST_Z	()	{ return 	std::get	<	FARTHEST_Z	>	(allParams);	}
	unsigned		get_INIT_WINDOW_WIDTH	()	{ return 	std::get	<	INIT_WINDOW_WIDTH	>	(allParams);	}
	unsigned		get_INIT_WINDOW_HEIGHT	()	{ return 	std::get	<	INIT_WINDOW_HEIGHT	>	(allParams);	}
	float*		get_BG_COLOR	()	{ return 	std::get	<	BG_COLOR	>	(allParams);	}
	float*		get_ALL_COLORS	()	{ return 	std::get	<	ALL_COLORS	>	(allParams);	}
	unsigned		get_COUNT_WHEELS	()	{ return 	std::get	<	COUNT_WHEELS	>	(allParams);	}
	unsigned		get_COUNT_SLOTS	()	{ return 	std::get	<	COUNT_SLOTS	>	(allParams);	}
	float		get_LEFT_SLOT_BORDER	()	{ return 	std::get	<	LEFT_SLOT_BORDER	>	(allParams);	}
	float		get_BOT_SLOT_BORDER	()	{ return 	std::get	<	BOT_SLOT_BORDER	>	(allParams);	}
	float		get_Z_SLOT_COORDINATE	()	{ return 	std::get	<	Z_SLOT_COORDINATE	>	(allParams);	}
	float		get_SLOT_WIDTH	()	{ return 	std::get	<	SLOT_WIDTH	>	(allParams);	}
	float		get_SLOT_HEIGHT	()	{ return 	std::get	<	SLOT_HEIGHT	>	(allParams);	}
	float		get_WHEEL_WIDTH	()	{ return 	std::get	<	WHEEL_WIDTH	>	(allParams);	}
	float		get_WHEEL_HEIGHT	()	{ return 	std::get	<	WHEEL_HEIGHT	>	(allParams);	}
	float		get_OFFSET_WHEEL	()	{ return 	std::get	<	OFFSET_WHEEL	>	(allParams);	}
	float		get_OFFSET_SLOT	()	{ return 	std::get	<	OFFSET_SLOT	>	(allParams);	}
	float		get_START_BUTTON_LEFT	()	{ return 	std::get	<	START_BUTTON_LEFT	>	(allParams);	}
	float		get_START_BUTTON_BOT	()	{ return 	std::get	<	START_BUTTON_BOT	>	(allParams);	}
	float		get_START_BUTTON_WIDTH	()	{ return 	std::get	<	START_BUTTON_WIDTH	>	(allParams);	}
	float		get_START_BUTTON_HEIGHT	()	{ return 	std::get	<	START_BUTTON_HEIGHT	>	(allParams);	}
	float*		get_WHEEL_DELAYED	()	{ return 	std::get	<	WHEEL_DELAYED	>	(allParams);	}
	float*		get_WHEEL_SLOWING	()	{ return 	std::get	<	WHEEL_SLOWING	>	(allParams);	}
	float*		get_WHEEL_SPEED	()	{ return 	std::get	<	WHEEL_SPEED	>	(allParams);	}
	float*		get_DRAW_FPS_POS	()	{ return 	std::get	<	DRAW_FPS_POS	>	(allParams);	}
	const char*		get_START_BUTTON_TEXTURE_1	()	{ return 	std::get	<	START_BUTTON_TEXTURE_1	>	(allParams).c_str();	}
	const char*		get_START_BUTTON_TEXTURE_2	()	{ return 	std::get	<	START_BUTTON_TEXTURE_2	>	(allParams).c_str();	}


	std::size_t size() {return std::tuple_size<decltype(allParams)>::value;}

private:
	std::tuple<
			unsigned		//	INITIAL_FPS
		,	float		//	SCENE_HORIZ_MIN
		,	float		//	SCENE_HORIZ_MAX
		,	float		//	SCENE_VERT_MIN
		,	float		//	SCENE_VERT_MAX
		,	float		//	NEAREST_Z
		,	float		//	FARTHEST_Z
		,	unsigned		//	INIT_WINDOW_WIDTH
		,	unsigned		//	INIT_WINDOW_HEIGHT
		,	float*		//	BG_COLOR
		,	float*		//	ALL_COLORS
		,	unsigned		//	COUNT_WHEELS
		,	unsigned		//	COUNT_SLOTS
		,	float		//	LEFT_SLOT_BORDER
		,	float		//	BOT_SLOT_BORDER
		,	float		//	Z_SLOT_COORDINATE
		,	float		//	SLOT_WIDTH
		,	float		//	SLOT_HEIGHT
		,	float		//	WHEEL_WIDTH
		,	float		//	WHEEL_HEIGHT
		,	float		//	OFFSET_WHEEL
		,	float		//	OFFSET_SLOT
		,	float		//	START_BUTTON_LEFT
		,	float		//	START_BUTTON_BOT
		,	float		//	START_BUTTON_WIDTH
		,	float		//	START_BUTTON_HEIGHT
		,	float*		//	WHEEL_DELAYED
		,	float*		//	WHEEL_SLOWING
		,	float*		//	WHEEL_SPEED
		,	float*		//	DRAW_FPS_POS
		,	std::string		//START_BUTTON_TEXTURE_1
		,	std::string		//START_BUTTON_TEXTURE_2
	> allParams;
};

}
