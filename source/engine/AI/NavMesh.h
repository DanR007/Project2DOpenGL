#pragma once
#include <glm/vec2.hpp>
#include <vector>

#include "../generators/RTSMapGenerator.h"

struct Cell;

enum class EResourceTypes;

class NavMeshRTS
{
public:
	NavMeshRTS(std::vector<std::vector<Cell*>> map);
	NavMeshRTS();

	~NavMeshRTS();

	void FillMap(std::vector<std::vector<Cell*>> map);
	
	std::vector<std::vector<Cell*>> GetMap();

	void ClearMapCell(const glm::ivec2& position);
	void OccupiedMapCell(const glm::ivec2& position);
	void SetMapCell(const glm::ivec2& position, const char& symbol);

	void PrintMap();

	bool InMap(const glm::ivec2& pos);

	Resource* GetNearestResource(const glm::ivec2& position, const EResourceTypes& type);
private:
	std::vector<std::vector<Cell*>> _map;

	friend class AStarRTS;
};