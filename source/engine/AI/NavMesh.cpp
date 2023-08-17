#include "NavMesh.h"

#include "../managers/GameManager.h"

#include "../../main.h"

#include <queue>
#include <iostream>

#include "../../game/ResourceTypes.h"
#include "../../game/gameobjects/Resource.h"

NavMeshRTS::NavMeshRTS(std::vector<std::vector<Cell*>> map)
{
	_map = map;
}

NavMeshRTS::NavMeshRTS()
{

}

NavMeshRTS::~NavMeshRTS()
{
}

void NavMeshRTS::FillMap(std::vector<std::vector<Cell*>> map)
{
	_map = map;
}

std::vector<std::vector<Cell*>> NavMeshRTS::GetMap()
{
	return _map;
}

void NavMeshRTS::ClearMapCell(const glm::ivec2& position)
{
	_map[position.y][position.x]->_symbol = '.';
}

void NavMeshRTS::OccupiedMapCell(const glm::ivec2& position)
{
	_map[position.y][position.x]->_symbol = 'B';
}

void NavMeshRTS::SetMapCell(const glm::ivec2& position, const char& symbol)
{
	_map[position.y][position.x]->_symbol = symbol;
}

void NavMeshRTS::PrintMap()
{
	std::cout <<"Print map: " << std::endl;
	for (size_t y = _map.size() - 1; y >= 0; y--)
	{
		for (size_t x = 0; x < _map.size(); x++)
		{
			std::cout << _map[y][x]->_symbol;
		}
		std::cout << std::endl;
	}
	std::cout << "End map " << std::endl;
}

bool NavMeshRTS::InMap(const glm::ivec2& pos)
{
	return _map.size() > pos.y && pos.y >= 0 && _map[0].size() > pos.x && pos.x >= 0;
}

Resource* NavMeshRTS::GetNearestResource(const glm::ivec2& position, const EResourceTypes& type)
{
	Cell* start = _map[position.y][position.x];
	std::queue<Cell*> q;

	std::vector<Cell*> cells;
	q.push(start);
	Cell* current;

	cells.push_back(current);

	while (!q.empty())
	{
		current = q.front();
		q.pop();
		
		std::vector<glm::ivec2> move =
		{
			glm::ivec2(0, 1), glm::ivec2(0, -1),
			glm::ivec2(1, 0), glm::ivec2(-1, 0)
		};

		for (int i = 0; i < 4; i++)
		{
			glm::ivec2 next = current->_position + move[i];
			if (InMap(next))
			{
				if (_map[next.y][next.x]->_resource && 
					_map[next.y][next.x]->_resource->GetResourceType() == type &&
					!_map[next.y][next.x]->_resource->IsEmpty())
				{
					return _map[next.y][next.x]->_resource;
				}
				else
				{
					std::vector<Cell*>::iterator it = std::find(cells.begin(), cells.end(), _map[next.y][next.x]);
					if (it == cells.end())
					{
						q.push(_map[next.y][next.x]);
						cells.push_back(_map[next.y][next.x]);
					}
				}
			}
		}

	}

	return nullptr;
}
