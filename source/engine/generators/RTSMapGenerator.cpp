#define _USE_MATH_DEFINES

#include "RTSMapGenerator.h"

#include "../math/Math.h"

#include <iostream>

RTSMapGenerator::RTSMapGenerator(const glm::ivec2& size)
{
	_size = size;

	_symbols = { GenSymbol(0.3f, 0.7f, 0.7f, 'W'), GenSymbol(0.7f, 0.7f, 0.4f, 'S')};
}

glm::vec2 RendomVector()
{
	int angle = std::rand() % 360;
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
	glm::vec2 rand_offset = glm::vec2(float(std::rand() % 11) / 10.f, float(std::rand() % 11) / 10.f);

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
	_map.resize(_size.y);

	for (int y = 0; y < _size.y; y++)
	{
		humidity_array[y].resize(_size.x);
		height_array[y].resize(_size.x);
		population_array[y].resize(_size.x);
		_map[y].resize(_size.x);

		for (int x = 0; x < _size.x; x++)
		{
			height_array[y][x] = FBM(glm::ivec2(x, y), 2);
			humidity_array[y][x] = FBM(glm::ivec2(x, y), 2);
			population_array[y][x] = FBM(glm::ivec2(x, y), 2);

			min_height = std::min(min_height, height_array[y][x]);
			min_humidity = std::min(min_humidity, humidity_array[y][x]);
			min_population = std::min(min_population, population_array[y][x]);

			max_height = std::max(max_height, height_array[y][x]);
			max_humidity = std::max(max_humidity, humidity_array[y][x]);
			max_population = std::max(max_population, population_array[y][x]);

		}
	}

	for (int y = 0; y < _size.y; y++)
	{
		for (int x = 0; x < _size.x; x++)
		{
			height_array[y][x] = (height_array[y][x] - min_height) / (max_height - min_height);
			humidity_array[y][x] = (humidity_array[y][x] - min_humidity) / (max_humidity - min_humidity);
			population_array[y][x] = (population_array[y][x] - min_population) / (max_population - min_population);

			_map[x][y] = Cell(glm::ivec2(x, y), 0, 1, GetSymbol(height_array[y][x], humidity_array[y][x], population_array[y][x]), 0);

			std::cout << _map[x][y]._symbol;

		}
		std::cout << std::endl;

	}

	/*_map =
	{
		{
			Cell(), Cell(glm::ivec2(1, 0), 0, 1, '.', 0), Cell(glm::ivec2(2, 0), 0, 1, '.', 0), Cell(glm::ivec2(3, 0), 0, -1, 'W'), Cell(glm::ivec2(4, 0), 0, 1, '.', 1), Cell(glm::ivec2(5, 0), 0, 1, '.', 1), Cell(glm::ivec2(6, 0), 0, 1, '.', 1)
		},
		{
			Cell(glm::ivec2(0, 1), 0, 1, '.', 0), Cell(glm::ivec2(1, 1)), Cell(glm::ivec2(2, 1), 0, -1, 'W'), Cell(glm::ivec2(3, 1), 0, -1, 'W'), Cell(glm::ivec2(4, 1), 0, 1, '.', 1), Cell(glm::ivec2(5, 1), 0, 1, '.', 1), Cell(glm::ivec2(6, 1), 0, 1, '.', 1)
		},
		{
			Cell(glm::ivec2(0, 2), 0, 1, '.', 0), Cell(glm::ivec2(1, 2)), Cell(glm::ivec2(2, 2), 0, -1, 'S'), Cell(glm::ivec2(3, 2), 0, 1, '.', 1), Cell(glm::ivec2(4, 2), 0, 1, '.', 1), Cell(glm::ivec2(5, 2), 0, 1, '.', 1), Cell(glm::ivec2(6, 2), 0, 1, '.', 1)
		},
		{
			Cell(glm::ivec2(0, 3), 0, 1, '.', 0), Cell(glm::ivec2(1, 3), 0, -1, 'B'), Cell(glm::ivec2(2, 3), 0, -1, 'S'), Cell(glm::ivec2(3, 3), 0, 1, '.', 1), Cell(glm::ivec2(4, 3), 0, 1, '.', 1), Cell(glm::ivec2(5, 3), 0, 1, '.', 1), Cell(glm::ivec2(6, 3), 0, 1, '.', 1)
		},
		{
			Cell(glm::ivec2(0, 4), 0, 1, '.', 0), Cell(glm::ivec2(1, 4), 0, -1, 'B'), Cell(glm::ivec2(2, 4), 0, 1, '.', 1), Cell(glm::ivec2(3, 4), 0, 1, '.', 1), Cell(glm::ivec2(4, 4), 0, 1, '.', 1), Cell(glm::ivec2(5, 4), 0, -1, 'B'), Cell(glm::ivec2(6, 4), 0, -1, 'B')
		},
		{
			Cell(glm::ivec2(0, 5), 0, 1, '.', 0), Cell(glm::ivec2(1, 5), 0, -1, 'B'), Cell(glm::ivec2(2, 5), 0, -1, 'B'), Cell(glm::ivec2(3, 5), 0, -1, 'B'), Cell(glm::ivec2(4, 5), 0, -1, 'B'), Cell(glm::ivec2(5, 5), 0, -1, 'B'), Cell(glm::ivec2(6, 5), 0, 1, '.', 0)
		},
		{
			Cell(glm::ivec2(0, 6), 0, 1, '.', 0), Cell(glm::ivec2(1, 6), 0, 1, '.', 0), Cell(glm::ivec2(2, 6), 0, 1, '.', 0), Cell(glm::ivec2(3, 6), 0, 1, '.', 0), Cell(glm::ivec2(4, 6), 0, 1, '.', 0), Cell(glm::ivec2(5, 6), 0, 1, '.', 0), Cell(glm::ivec2(6, 6), 0, 1, '.', 0)
		}
	};*/
	/*{
			Cell(glm::ivec2(0), 0, -1, 'B'), Cell(glm::ivec2(1, 0), 0, -1, 'B'), Cell(glm::ivec2(2, 0), 0, -1, 'B'), Cell(glm::ivec2(3, 0), 0, -1, 'B'), Cell(glm::ivec2(4, 0)), Cell(glm::ivec2(5, 0)), Cell(glm::ivec2(6, 0))
		},
		{
			Cell(glm::ivec2(0, 1), 0, -1, 'B'), Cell(glm::ivec2(1, 1)), Cell(glm::ivec2(2, 1), 0, -1, 'B'), Cell(glm::ivec2(3, 1), 0, -1, 'B'), Cell(glm::ivec2(4, 1)), Cell(glm::ivec2(5, 1), 0, 4), Cell(glm::ivec2(6, 1), 0, 4)
		},
		{
			Cell(glm::ivec2(0, 2), 0, -1, 'B'), Cell(glm::ivec2(1, 2)), Cell(glm::ivec2(2, 2), 0, 5), Cell(glm::ivec2(3, 2), 0, 5), Cell(glm::ivec2(4, 2), 0, 4), Cell(glm::ivec2(5, 2), 0, 4), Cell(glm::ivec2(6, 2), 0, 4)
		},
		{
			Cell(glm::ivec2(0, 3), 0, -1, 'B'), Cell(glm::ivec2(1, 3), 0, 5), Cell(glm::ivec2(2, 3), 0, 5), Cell(glm::ivec2(3, 3), 0, 5), Cell(glm::ivec2(4, 3)), Cell(glm::ivec2(5, 3)), Cell(glm::ivec2(6, 3))
		},
		{
			Cell(glm::ivec2(0, 4)), Cell(glm::ivec2(1, 4), 0, 1), Cell(glm::ivec2(2, 4), 0, -1, 'B'), Cell(glm::ivec2(3, 4)), Cell(glm::ivec2(4, 4)), Cell(glm::ivec2(5, 4), 0, -1, 'B'), Cell(glm::ivec2(6, 4), 0, -1, 'B')
		},
		{
			Cell(glm::ivec2(0, 5), 0, -1, 'B'), Cell(glm::ivec2(1, 5), 0, -1, 'B'), Cell(glm::ivec2(2, 5), 0, -1, 'B'), Cell(glm::ivec2(3, 5)), Cell(glm::ivec2(4, 5), 0, -1, 'B'), Cell(glm::ivec2(5, 5), 0, -1, 'B'), Cell(glm::ivec2(6, 5))
		},
		{
			Cell(glm::ivec2(0, 6), 0, -1, 'B'), Cell(glm::ivec2(1, 6)), Cell(glm::ivec2(2, 6)), Cell(glm::ivec2(3, 6)), Cell(glm::ivec2(4, 6)), Cell(glm::ivec2(5, 6)), Cell(glm::ivec2(6, 6))
		}*/
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

char RTSMapGenerator::GetSymbol(const float& height, const float& humidity, const float& population)
{
	for (int i = 0; i < _symbols.size(); i++)
	{
		if (_symbols[i]._height < height && _symbols[i]._humidity < humidity && _symbols[i]._population < population)
			return _symbols[i]._symbol;
	}

	return ' ';
}


