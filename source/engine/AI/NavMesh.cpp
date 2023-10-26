#include "NavMesh.h"

#include "../managers/GameManager.h"

#include "../../main.h"

#include <queue>
#include <iostream>

#ifdef __linux__
#include <algorithm>
#endif //__linux__

#include "../../game/ResourceTypes.h"
#include "../../game/gameobjects/Resource.h"

#include "../math/Algorithm.h"

bool CheckEqualsResourceType(const EResourceTypes& type, Cell* cell)
{
	if(!cell->_resource)
	{
#ifdef DEBUG
		std::cout << "In this cell (x, y) no resource: (" 
		<< cell->_position.x 
		<< ", "
		<< cell->_position.y 
		<< ")"
		<< std::endl;
#endif //DEBUG
		return false;
	}
	
	return cell->_resource->GetResourceType() == type;
}

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

	RefillAllID();
}

std::vector<std::vector<Cell*>> NavMeshRTS::GetMap()
{
	return _map;
}

void NavMeshRTS::ClearMapCell(const glm::ivec2& position)
{
	_map[position.y][position.x]->_symbol = '.';
	_map[position.y][position.x]->_resource = nullptr;

	RefillAllID();
#ifdef DEBUG
	PrintMap();
#endif //DEBUG
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
	for (int y = _map.size() - 1; y >= 0; y--)
	{
		for (int x = 0; x < _map[y].size(); x++)
		{
			std::cout << _map[y][x]->_field_id;
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
	glm::ivec2 nearest_resource_coordinates = Algorithm::BFS(_map, position, type, CheckEqualsResourceType);

	if(nearest_resource_coordinates == glm::ivec2(-1, -1))
	{
		return nullptr;
	}

	return _map[nearest_resource_coordinates.y][nearest_resource_coordinates.x]->_resource;
}

void NavMeshRTS::RefillAllID()
{
	unsigned short int num = 0;

	for (int i = 0; i < _map.size(); i++)
	{
		for (int j = 0; j < _map[i].size(); j++)
		{
			if (IsFreeCell(glm::ivec2(j, i))
			&& _map[i][j]->_field_id != num)
			{
				RefillIDInBreadth(glm::ivec2(j, i), num++);
			}
		}
	}
}

void NavMeshRTS::RefillIDInBreadth(const glm::ivec2& start, unsigned short int id)
{
	std::queue<glm::ivec2> q;

	q.push(start);

	_map[start.y][start.x]->_field_id = id;

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

			if (InMap(neighbour) && IsFreeCell(neighbour))
			{
				q.push(neighbour);
				_map[neighbour.y][neighbour.x]->_field_id = id;
			}

		}
	}
}
