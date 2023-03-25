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

void NavMeshRTS::FillMap(std::vector<std::vector<Cell>>& map)
{
	_map = map;
}

std::vector<std::vector<Cell>> NavMeshRTS::GetMap()
{
	return _map;
}
