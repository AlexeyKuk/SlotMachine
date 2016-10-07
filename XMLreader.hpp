/*
 * XMLreader.hpp
 *
 *  Created on: Oct 6, 2016
 *      Author: alex
 */

#include "tinyxml2.h"

#include <iostream>
#include <sstream>
#include <vector>


template<typename T>
T str_to_out(const std::string &str)
{
	std::cout << "Type in str_to_out NOT found" << std::endl;
	std::terminate();
	return (T)0;
}

template<>
unsigned str_to_out(const std::string &str);

template<>
float str_to_out(const std::string &str);

// get float array
template<>
float* str_to_out(const std::string &str);

template<>
std::string str_to_out(const std::string &str);


template<typename T>
T read_elem_from_xml(const char * name)
{
	tinyxml2::XMLDocument xmlDoc;

//	std::cout << "Load xml" << std::endl;

	if (xmlDoc.LoadFile("config.xml"))
		std::terminate();

//	std::cout << "Start to read param with name : " << name << std::endl;

	tinyxml2::XMLNode * element = xmlDoc.RootElement(); //->FirstChild();

//	std::cout << "get value" << std::endl;

	std::string str = element->FirstChildElement(name)->FirstChild()->Value();

//	std::cout << "param : " << name << "  val : " << str << std::endl;

	return str_to_out<T>(str);
}

void xml_read();
