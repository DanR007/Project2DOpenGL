#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <map>

class XMLFile;
class XMLElement;
class XMLAttribute;


class XMLFile
{
public:
    XMLFile(const std::string& exe_path);

    void StartReadingFile(const std::string& file_name);
    
    std::vector<XMLElement> ReadChildElement(const std::string& name_element, const XMLElement& root_element);
    std::vector<XMLElement> ReadElement(const std::string& element_name);
    
private:
    std::string _exe_path;
    
    std::vector<std::string> _full_file;
};

class XMLElement
{
public:
    XMLElement(const std::string& element_line, const size_t start_index, const size_t end_index);

    size_t GetStart() const { return _start_line_id; }
    size_t GetEnd() const { return _end_line_id; }
    std::string GetLine() const { return _element_line; }

    XMLAttribute ReadAttribute(const std::string& attribute_name);
    XMLAttribute GetAttribute(const std::string& attribute_name);

private:
    size_t _start_line_id, _end_line_id;
    std::string _element_line;

    std::map<std::string, XMLAttribute> attribute_map;
};

class XMLAttribute
{
public:
    XMLAttribute(const std::string& attribute);

    std::string GetData() const { return _attribute_data; }
private:
    std::string _attribute_data;
};