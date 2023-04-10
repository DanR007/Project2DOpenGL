#pragma once 
#include <glm/vec2.hpp>

#include <vector>
#include <string>

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

struct GenSymbol
{
	GenSymbol(float height, float population, float humidity, char symbol)
	{
		_height = height;
		_population = population;
		_humidity = humidity;

		_symbol = symbol;
	}
	float _height, _population, _humidity;

	char _symbol;
};

class RTSMapGenerator
{
public:
	RTSMapGenerator(const glm::ivec2& size);

	float Noise(const glm::ivec2& pos);
	float FBM(const int& count, int x, int y);

	std::vector<std::vector<Cell>> GenerateMap();

	float FBM(const glm::ivec2& pos, const int& count);
private:
	char GetSymbol(const float& height, const float& humidity, const float& population);

	glm::ivec2 _size;

	std::vector<std::vector<Cell>> _map;

	std::vector<std::vector<glm::vec2>> _rand_vectors;

	std::vector<GenSymbol> _symbols;
};