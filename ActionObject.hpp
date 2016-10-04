/*
 * ActionObject.hpp
 *
 *  Created on: Oct 3, 2016
 *      Author: alex
 */

#pragma once


class ActionObject
{
public:

	virtual void on_click() = 0;

	virtual bool is_clicked(float xCoord, float yCoord) const = 0;

	virtual void draw() = 0;

	virtual ~ActionObject() {}

};
