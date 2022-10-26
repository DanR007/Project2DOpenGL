#include "XMLParser.h"

#include <iostream>
#include <iterator>

XMLFile::XMLFile(const std::string& exe_path)
{
	_exe_path = exe_path.substr(0, exe_path.find_last_of("/\\"));
}

void XMLFile::StartReadingFile(const std::string& file_name)
{
	std::ifstream _xml_file;
	std::string mst = _exe_path + '/' + file_name;
	_xml_file.open(_exe_path + '/' + file_name);
	std::string str = "";
	while (std::getline(_xml_file, str))
	{
		_full_file.push_back(str);
	}
}

std::vector<XMLElement> XMLFile::ReadChildElement(const std::string& name_element, const XMLElement& root_element)
{
	std::vector<XMLElement> xml_elements;
	std::size_t ind_st;

	for (size_t i = root_element.GetStart() + 1; i < root_element.GetEnd(); i++)
	{
		std::size_t ind_end = _full_file[i].find('/' + name_element), ind = _full_file[i].find("<"+name_element);
		if (ind != std::string::npos)
			ind_st = i;
		if (ind_end != std::string::npos)
			xml_elements.push_back(XMLElement(_full_file[ind_st], ind_st, i));

	}

	return xml_elements;
}

std::vector<XMLElement> XMLFile::ReadElement(const std::string& element_name)
{
	std::vector<XMLElement> xml_elements;
	std::size_t ind_st;
	for (size_t i = 0; i < _full_file.size(); i++)
	{
		std::size_t ind_end = _full_file[i].find("</" + element_name + '>'), ind = _full_file[i].find("<" + element_name);
		if (ind != std::string::npos)
			ind_st = i;
		if (ind_end != std::string::npos)
			xml_elements.push_back(XMLElement(_full_file[ind_st], ind_st, i));
	}
	return xml_elements;
}

XMLAttribute XMLElement::ReadAttribute(const std::string& attribute_name)
{
	size_t start = _element_line.find(attribute_name + "=\"") + attribute_name.size() + 2, end = _element_line.find("\"", start);
	return attribute_map.emplace(attribute_name, XMLAttribute(_element_line.substr(start, end - start))).first->second;
}

XMLAttribute XMLElement::GetAttribute(const std::string& attribute_name)
{
	std::map<std::string, XMLAttribute>::iterator it = attribute_map.find(attribute_name);

	if (it == attribute_map.end())
	{
		std::cerr << "Can not find attribute with name: " + attribute_name << std::endl;
		return NULL;
	}

	return it->second;
}

XMLElement::XMLElement(const std::string& element_line, const size_t start_index, const size_t end_index)
{
	_element_line = element_line;
	_start_line_id = start_index;
	_end_line_id = end_index;
}

XMLAttribute::XMLAttribute(const std::string& attribute)
{
	_attribute_data = attribute;
}
