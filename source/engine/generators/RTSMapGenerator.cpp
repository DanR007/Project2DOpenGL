#define _USE_MATH_DEFINES

#include "RTSMapGenerator.h"

#include "../math/Math.h"

#include <iostream>
#include <iomanip>
#include <queue>


RTSMapGenerator::RTSMapGenerator(const glm::ivec2& size)
{
	_size = size;
	//height population (normalize) humidity
	_symbols = { GenSymbol(0.f, 0.6f, 0.f, 'W'), GenSymbol(0.3f, 0.6f, -0.1f, 'S')};
}

glm::vec2 RendomVector()
{
	int angle = std::rand() & 360;
	float rad_angle = float(angle) * M_PI / 180.f;
	return glm::vec2(std::cos(rad_angle), std::sin(rad_angle));
}

float Fade(float t) 
{
	return ((6 * t - 15) * t + 10) * t * t * t;
}

float Lerp(float t, float a1, float a2) 
{
	return a1 + t * (a2 - a1);
}

float RTSMapGenerator::Noise(const glm::ivec2& pos)
{
	glm::vec2 rand_offset = glm::vec2(float(std::rand() % 10 + 1) / 10.f, float(std::rand() % 10 + 1) / 10.f);

	glm::vec2 left_bottom, left_top, right_top, right_bottom;

	left_bottom = rand_offset;
	left_top = glm::vec2(rand_offset.x, rand_offset.y - 1);
	right_top = rand_offset - glm::vec2(1.f);
	right_bottom = glm::vec2(rand_offset.x - 1, rand_offset.y);

	
	float dot_top_left = Math::DOT(_rand_vectors[pos.y + 1][pos.x], left_top);
	float dot_top_right = Math::DOT(_rand_vectors[pos.y + 1][pos.x + 1], right_top);
	float dot_bottom_left = Math::DOT(_rand_vectors[pos.y][pos.x], left_bottom);
	float dot_bottom_right = Math::DOT(_rand_vectors[pos.y][pos.x + 1], right_bottom);

	const float u = Fade(rand_offset.x);
	const float v = Fade(rand_offset.y);

	return Lerp(u,
		Lerp(v, dot_bottom_left, dot_top_left),
		Lerp(v, dot_bottom_right, dot_top_right)
	);

}

std::vector<std::vector<Cell>> RTSMapGenerator::GenerateMap()
{
	std::vector<std::vector<float>> humidity_array;
	std::vector<std::vector<float>> height_array;
	std::vector<std::vector<float>> population_array;

	std::vector<std::vector<char>> symbol_array;

	//also I should use RandomVector()

	std::vector<glm::vec2> const_vectors =
	{
		glm::vec2(1.f, 0.f), glm::vec2(-1.f, 0.f), glm::vec2(0.f, -1.f), glm::vec2(0, 1.f)
	};


	_rand_vectors.resize(_size.y + 1);


	for (int y = 0; y < _size.y + 1; y++)
	{
		_rand_vectors[y].resize(_size.x + 1);
		for (int x = 0; x < _size.x + 1; x++)
		{
			_rand_vectors[y][x] = const_vectors[std::rand() & 3];
		}
	}

	float min_height = FLT_MAX;
	float min_humidity = FLT_MAX;
	float min_population = FLT_MAX;
	float max_height = FLT_MIN;
	float max_humidity = FLT_MIN;
	float max_population = FLT_MIN;

	humidity_array.resize(_size.y);
	height_array.resize(_size.y);
	population_array.resize(_size.y);
	symbol_array.resize(_size.y);

	_map.resize(_size.y);

	for (int y = 0; y < _size.y; y++)
	{
		humidity_array[y].resize(_size.x);
		height_array[y].resize(_size.x);
		population_array[y].resize(_size.x);
		symbol_array[y].resize(_size.x);

		_map[y].resize(_size.x);

		for (int x = 0; x < _size.x; x++)
		{
			height_array[y][x] = FBM(glm::ivec2(x, y), 2);
			humidity_array[y][x] = FBM(glm::ivec2(x, y), 2);
			population_array[y][x] = FBM(glm::ivec2(x, y), 2);

			/*min_height = std::min(min_height, height_array[y][x]);
			min_humidity = std::min(min_humidity, humidity_array[y][x]);

			max_height = std::max(max_height, height_array[y][x]);
			max_humidity = std::max(max_humidity, humidity_array[y][x]);*/
			min_population = std::min(min_population, population_array[y][x]);
			max_population = std::max(max_population, population_array[y][x]);

		}
	}

	//_symbols[0]._humidity = (max_humidity + min_humidity) / 2.f;

	for (int y = 0; y < _size.y; y++)
	{
		for (int x = 0; x < _size.x; x++)
		{
			//height_array[y][x] = (height_array[y][x] - min_height) / (max_height - min_height);
			//humidity_array[y][x] = (humidity_array[y][x] - min_humidity) / (max_humidity - min_humidity);
			population_array[y][x] = (population_array[y][x] - min_population) / (max_population - min_population);

			_map[y][x] = Cell(glm::ivec2(x, y), 0, 1, GetSymbol(height_array[y][x], humidity_array[y][x], population_array[y][x]), 0);

			std::cout << _map[y][x]._symbol;

		}
		std::cout << std::endl;

	}
	std::cout <<"/////////////////" << std::endl;
	CellularAutomaton(4, _symbols[0]._symbol);
	CellularAutomaton(3, _symbols[0]._symbol);

	CellularAutomaton(2, _symbols[1]._symbol);

	for (int y = 0; y < _size.y; y++)
	{
		for (int x = 0; x < _size.x; x++)
		{
			std::cout << _map[y][x]._symbol;
			symbol_array[y][x] = _map[y][x]._symbol;
		}
		std::cout << std::endl;

	}
	std::cout << "/////////////////" << std::endl;
	FillFieldID(symbol_array);

	for (int y = 0; y < _size.y; y++)
	{
		for (int x = 0; x < _size.x; x++)
		{
			std::cout << _map[y][x]._field_id;
		}
		std::cout << std::endl;

	}

	return _map;
}

float RTSMapGenerator::FBM(const glm::ivec2& pos, const int& count)
{
	float amplitude = 1.f;
	float result = 0;

	for (int i = 0; i < count; i++)
	{
		result += amplitude * Noise(pos);
		amplitude /= 2;
	}

	return result;
}



void RTSMapGenerator::CellularAutomaton(const int& count_life_cells_need, const char& symbol)
{
	std::vector<std::vector<char>> cell_condition;

	cell_condition.resize(_size.y);

	for (int y = 0; y < _size.y; y++)
	{
		cell_condition[y].resize(_size.x);

		for (int x = 0; x < _size.x; x++)
		{
			if (_map[y][x]._symbol == symbol)
			{
				if (GetLifeCell(glm::ivec2(x, y), _map[y][x]._symbol) >= count_life_cells_need)
				{
					cell_condition[y][x] = _map[y][x]._symbol;
				}
				else
				{
					cell_condition[y][x] = ' ';
				}
			}
			else
			{
				cell_condition[y][x] = _map[y][x]._symbol;
			}
		}
	}

	for (int y = 0; y < _size.y; y++)
	{
		for (int x = 0; x < _size.x; x++)
		{
			_map[y][x]._symbol = cell_condition[y][x];
		}
	}
}

void RTSMapGenerator::FillFieldID(std::vector<std::vector<char>>& map)
{
	unsigned short int num = 0;

	for (int i = 0; i < _size.y; i++)
	{
		for (int j = 0; j < _size.x; j++)
		{
			if (map[i][j] == ' ')
			{
				BFS(glm::ivec2(j, i), map, num++);
			}
		}
	}
}

void RTSMapGenerator::BFS(const glm::ivec2& start, std::vector<std::vector<char>>& map, unsigned short int id)
{
	std::queue<glm::ivec2> q;

	q.push(start);

	map[start.y][start.x] = '.';
	_map[start.y][start.x]._field_id = id;

	std::vector<glm::ivec2> neighbours =
	{
		glm::ivec2(1, 0),
		glm::ivec2(-1, 0),
		glm::ivec2(0, 1),
		glm::ivec2(0, -1)
	};

	while (!q.empty())
	{
		glm::ivec2 cur = q.front();
		q.pop();

		for (int i = 0; i < neighbours.size(); i++)
		{
			glm::ivec2 neighbour = cur + neighbours[i];

			if (neighbour.x >= 0 && neighbour.y >= 0 && neighbour.x < _size.x && neighbour.y < _size.y && map[neighbour.y][neighbour.x] == ' ')
			{
				q.push(neighbour);
				map[neighbour.y][neighbour.x] = '.';
				_map[neighbour.y][neighbour.x]._field_id = id;
			}

		}
	}
}


size_t RTSMapGenerator::GetLifeCell(const glm::ivec2& pos, const char& life_symbol)
{
	size_t count = 0;

	std::vector<glm::ivec2> neighbours =
	{
		glm::ivec2(1, 0),
		glm::ivec2(-1, 0),
		glm::ivec2(0, 1),
		glm::ivec2(0, -1),

		glm::ivec2(1, 1),
		glm::ivec2(-1, 1),
		glm::ivec2(-1, -1),
		glm::ivec2(1, -1)
	};

	for (int i = 0; i < neighbours.size(); i++)
	{
		glm::ivec2 neighbour = pos + neighbours[i];

		if (neighbour.x >= 0 && neighbour.y >= 0 && neighbour.x < _size.x && neighbour.y < _size.y)
		{
			count += _map[neighbour.y][neighbour.x]._symbol == life_symbol ? 1 : 0;
		}

	}

	return count;
}

char RTSMapGenerator::GetSymbol(const float& height, const float& humidity, const float& population)
{
	for (int i = 0; i < _symbols.size(); i++)
	{
		if (/*_symbols[i]._height < height && */_symbols[i]._humidity < humidity/* && _symbols[i]._population < population*/)
			return _symbols[i]._symbol;
	}

	return ' ';
}


