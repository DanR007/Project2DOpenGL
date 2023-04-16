#include "NavMesh.h"

#include "../managers/GameManager.h"

#include "../../main.h"

#include <queue>
#include <iostream>

NavMeshRTS::NavMeshRTS(std::vector<std::vector<Cell>>& map)
{
	_map = map;
}

NavMeshRTS::NavMeshRTS()
{

}

NavMeshRTS::~NavMeshRTS()
{
}

void NavMeshRTS::FillMap(std::vector<std::vector<Cell>>& map)
{
	_map = map;
}

std::vector<std::vector<Cell>> NavMeshRTS::GetMap()
{
	return _map;
}

void NavMeshRTS::ClearMapCell(const glm::ivec2& position)
{
	_map[position.y][position.x]._symbol = '.';
}

void NavMeshRTS::OccupiedMapCell(const glm::ivec2& position)
{
	_map[position.y][position.x]._symbol = 'B';
}

void NavMeshRTS::SetMapCell(const glm::ivec2& position, const char& symbol)
{
	_map[position.y][position.x]._symbol = symbol;
}

void NavMeshRTS::PrintMap()
{
	std::cout <<"Print map: " << std::endl;
	for (int y = _map.size() - 1; y >= 0; y--)
	{
		for (int x = 0; x < _map.size(); x++)
		{
			std::cout << _map[y][x]._symbol;
		}
		std::cout << std::endl;
	}
	std::cout << "End map " << std::endl;
}
