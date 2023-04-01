#pragma once 
#include <glm/vec2.hpp>

#include <vector>
#include <string>
#include <cmath>

struct Cell
{
	Cell(const glm::ivec2& position, const short int& height = 0, const short int& cost = 1, const char& symbol = '.', const unsigned short int& field_id = 0):
		_height(height), _cost(cost), _position(position), _symbol(symbol), _field_id(field_id)
	{

	}
	Cell()
	{
		_height = 0;
		_cost = 1;
		_position = glm::ivec2(0);
		_symbol = '.';
		_field_id = 0;
	}

	bool operator!= (const Cell& c)
	{
		return c._position != _position;
	}
	bool operator== (const Cell& c)
	{
		return c._position == _position;
	}
	glm::ivec2 _position;

	short int _height, _cost;
	unsigned short int _field_id;
	char _symbol;
};


class RTSMapGenerator
{
public:
	RTSMapGenerator(const glm::ivec2& size);

	std::vector<std::vector<Cell>> GenerateMap();

private:
	glm::ivec2 _size;
};