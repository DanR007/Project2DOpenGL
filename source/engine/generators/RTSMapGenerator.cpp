#include "RTSMapGenerator.h"

RTSMapGenerator::RTSMapGenerator(const glm::ivec2& size)
{
	_size = size;
}

std::vector<std::vector<Cell>> RTSMapGenerator::GenerateMap()
{
	std::vector<std::vector<Cell>> map;

	map =
	{
		{
			Cell(), Cell(glm::ivec2(1, 0), 0, 1, '.', 0), Cell(glm::ivec2(2, 0), 0, 1, '.', 0), Cell(glm::ivec2(3, 0), 0, -1), Cell(glm::ivec2(4, 0), 0, 1, '.', 1), Cell(glm::ivec2(5, 0), 0, 1, '.', 1), Cell(glm::ivec2(6, 0), 0, 1, '.', 1)
		},
		{
			Cell(glm::ivec2(0, 1), 0, 1, '.', 0), Cell(glm::ivec2(1, 1)), Cell(glm::ivec2(2, 1), 0, -1), Cell(glm::ivec2(3, 1), 0, -1), Cell(glm::ivec2(4, 1), 0, 1, '.', 1), Cell(glm::ivec2(5, 1), 0, 1, '.', 1), Cell(glm::ivec2(6, 1), 0, 1, '.', 1)
		},
		{
			Cell(glm::ivec2(0, 2), 0, 1, '.', 0), Cell(glm::ivec2(1, 2)), Cell(glm::ivec2(2, 2), 0, -1, 'B'), Cell(glm::ivec2(3, 2), 0, 1, '.', 1), Cell(glm::ivec2(4, 2), 0, 1, '.', 1), Cell(glm::ivec2(5, 2), 0, 1, '.', 1), Cell(glm::ivec2(6, 2), 0, 1, '.', 1)
		},
		{
			Cell(glm::ivec2(0, 3), 0, 1, '.', 0), Cell(glm::ivec2(1, 3), 0, -1), Cell(glm::ivec2(2, 3), 0, -1), Cell(glm::ivec2(3, 3), 0, 1, '.', 1), Cell(glm::ivec2(4, 3), 0, 1, '.', 1), Cell(glm::ivec2(5, 3), 0, 1, '.', 1), Cell(glm::ivec2(6, 3), 0, 1, '.', 1)
		},
		{
			Cell(glm::ivec2(0, 4), 0, 1, '.', 0), Cell(glm::ivec2(1, 4), 0, -1), Cell(glm::ivec2(2, 4), 0, 1, '.', 1), Cell(glm::ivec2(3, 4), 0, 1, '.', 1), Cell(glm::ivec2(4, 4), 0, 1, '.', 1), Cell(glm::ivec2(5, 4), 0, -1), Cell(glm::ivec2(6, 4), 0, -1)
		},
		{
			Cell(glm::ivec2(0, 5), 0, 1, '.', 0), Cell(glm::ivec2(1, 5), 0, -1), Cell(glm::ivec2(2, 5), 0, -1), Cell(glm::ivec2(3, 5), 0, -1), Cell(glm::ivec2(4, 5), 0, -1), Cell(glm::ivec2(5, 5), 0, -1), Cell(glm::ivec2(6, 5), 0, 1, '.', 0)
		},
		{
			Cell(glm::ivec2(0, 6), 0, 1, '.', 0), Cell(glm::ivec2(1, 6), 0, 1, '.', 0), Cell(glm::ivec2(2, 6), 0, 1, '.', 0), Cell(glm::ivec2(3, 6), 0, 1, '.', 0), Cell(glm::ivec2(4, 6), 0, 1, '.', 0), Cell(glm::ivec2(5, 6), 0, 1, '.', 0), Cell(glm::ivec2(6, 6), 0, 1, '.', 0)
		}
		/*{
			Cell(glm::ivec2(0), 0, -1), Cell(glm::ivec2(1, 0), 0, -1), Cell(glm::ivec2(2, 0), 0, -1), Cell(glm::ivec2(3, 0), 0, -1), Cell(glm::ivec2(4, 0)), Cell(glm::ivec2(5, 0)), Cell(glm::ivec2(6, 0))
		},
		{
			Cell(glm::ivec2(0, 1), 0, -1), Cell(glm::ivec2(1, 1)), Cell(glm::ivec2(2, 1), 0, -1), Cell(glm::ivec2(3, 1), 0, -1), Cell(glm::ivec2(4, 1)), Cell(glm::ivec2(5, 1), 0, 4), Cell(glm::ivec2(6, 1), 0, 4)
		},
		{
			Cell(glm::ivec2(0, 2), 0, -1), Cell(glm::ivec2(1, 2)), Cell(glm::ivec2(2, 2), 0, 5), Cell(glm::ivec2(3, 2), 0, 5), Cell(glm::ivec2(4, 2), 0, 4), Cell(glm::ivec2(5, 2), 0, 4), Cell(glm::ivec2(6, 2), 0, 4)
		},
		{
			Cell(glm::ivec2(0, 3), 0, -1), Cell(glm::ivec2(1, 3), 0, 5), Cell(glm::ivec2(2, 3), 0, 5), Cell(glm::ivec2(3, 3), 0, 5), Cell(glm::ivec2(4, 3)), Cell(glm::ivec2(5, 3)), Cell(glm::ivec2(6, 3))
		},
		{
			Cell(glm::ivec2(0, 4)), Cell(glm::ivec2(1, 4), 0, 1), Cell(glm::ivec2(2, 4), 0, -1), Cell(glm::ivec2(3, 4)), Cell(glm::ivec2(4, 4)), Cell(glm::ivec2(5, 4), 0, -1), Cell(glm::ivec2(6, 4), 0, -1)
		},
		{
			Cell(glm::ivec2(0, 5), 0, -1), Cell(glm::ivec2(1, 5), 0, -1), Cell(glm::ivec2(2, 5), 0, -1), Cell(glm::ivec2(3, 5)), Cell(glm::ivec2(4, 5), 0, -1), Cell(glm::ivec2(5, 5), 0, -1), Cell(glm::ivec2(6, 5))
		},
		{
			Cell(glm::ivec2(0, 6), 0, -1), Cell(glm::ivec2(1, 6)), Cell(glm::ivec2(2, 6)), Cell(glm::ivec2(3, 6)), Cell(glm::ivec2(4, 6)), Cell(glm::ivec2(5, 6)), Cell(glm::ivec2(6, 6))
		}*/
	};

	return map;
}