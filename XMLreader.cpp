/*
 * XMLreader.cpp
 *
 *  Created on: Oct 7, 2016
 *      Author: alex
 */


#include "XMLreader.hpp"

template<>
unsigned str_to_out(const std::string &str)
{
	return std::stoi(str);
}

template<>
float str_to_out(const std::string &str)
{
	return std::stof(str);
}

// get array
template<>
float* str_to_out(const std::string &str)
{
	std::istringstream fin(str);
	std::vector<float> val;

	while(!fin.eof())
	{
		float f_val;
		fin >> f_val;
		val.push_back(f_val);
	}


	float * res = new float[val.size()];
	for (std::size_t i = 0; i < val.size(); ++i)
		res[i] = val[i];

	return res;
}


template<>
std::string str_to_out(const std::string &str)
{
	std::string res(str);
	return res;
}


void xml_read()
{
	tinyxml2::XMLDocument xmlDoc;

	if (xmlDoc.LoadFile("config.xml"))
		return;

	tinyxml2::XMLNode * element = xmlDoc.RootElement()->FirstChild();

	while (element)
	{
		std::cout << "XML param name : " << element->Value() << std::endl;
		std::cout << "XML value : " << element->FirstChild()->Value() << std::endl;
		element = element->NextSibling();
	}

	//print root Element
	std::cout << "XML root : " << xmlDoc.RootElement()->Value() << std::endl;

	std::cout << "XML text : " << xmlDoc.RootElement()->FirstChild()->FirstChild()->Value() << std::endl;

	std::cout << "XML text : " << xmlDoc.RootElement()->FirstChildElement("X_COORD")->FirstChild()->Value() << std::endl;


}









