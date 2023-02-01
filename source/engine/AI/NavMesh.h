#pragma once
#include <glm/vec2.hpp>
#include <vector>
#include <string>
#include <list>


namespace Game
{
	class Actor;
}

namespace p2t
{
	class CDT;
	class Triangle;
	struct Point;
}

class NavMesh
{
public:
	NavMesh();
	~NavMesh();

	void CreateNavMesh(std::vector<std::string>&, const glm::vec2 actors_size, const glm::vec2& block_size);

	void FillArrayOfPoints(std::vector<std::string>& map, const glm::vec2& block_size);
private:
	bool CheckCorner(const std::vector<std::string>& map, const glm::ivec2 current_pos,
		const glm::ivec2& corner_f, const glm::ivec2& corner_s, const glm::ivec2& checking);


	p2t::CDT* _cdt;

	std::vector<p2t::Point*> _points;
	std::vector<p2t::Triangle*> _triangles;

	std::list<p2t::Triangle*> _map;
};