#pragma once
#include <glm/vec2.hpp>
#include <vector>

#include "../generators/RTSMapGenerator.h"

struct Cell;

class NavMeshRTS
{
public:
	NavMeshRTS(std::vector<std::vector<Cell>>& map);
	NavMeshRTS();

	~NavMeshRTS();

	void FillMap(std::vector<std::vector<Cell>>& map);
	
	std::vector<std::vector<Cell>> GetMap();
private:
	std::vector<std::vector<Cell>> _map;

	friend class AStarRTS;
};