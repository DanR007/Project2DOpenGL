#include "NavMesh.h"

#include "poly2tri/poly2tri.h"

#include <queue>
#include <iostream>

NavMesh::NavMesh()
{

}

NavMesh::~NavMesh()
{
	for (p2t::Point* p : _points)
	{
		if(p)
		delete p;
		p = nullptr;
	}

	_triangles.clear();
	_map.clear();
	_points.clear();

	if(_cdt)
	delete _cdt;
	_cdt = nullptr;
}

void NavMesh::FillArrayOfPoints(std::vector<std::string>& map, const glm::vec2& block_size)
{
	char wall = 'W', checked_wall = 'w', free = '.';

	glm::ivec2 point_start;
	bool flag = false;
	for (int i = map.size() - 1; i >= 0; i--)//y
	{
		for (int j = 0; j < map[i].size(); j++)//x
		{
			if (map[i][j] == wall)
			{
				_points.push_back(new p2t::Point(glm::dvec2((j + 0.5) * block_size.x, (i - 0.5) * block_size.y)));
				point_start = glm::ivec2(j, i);
				map[i][j] = checked_wall;
				flag = true;
				break;
			}
		}
		if (flag)
			break;
	}

	glm::ivec2 move = glm::ivec2(1, 0);

	glm::ivec2 next = point_start + move;
	glm::ivec2 current_pos = point_start;

	std::vector<glm::ivec2> move_arr = 
	{
		glm::ivec2(0, 1),
		glm::ivec2(0, -1),
		glm::ivec2(1, 0),
		glm::ivec2(-1, 0)
	};
	std::vector<glm::ivec2> corner_arr =
	{
		glm::ivec2(-1, -1),
		glm::ivec2(1, 1),
		glm::ivec2(1, -1),
		glm::ivec2(-1, 1)
	};
	glm::ivec2 old_move;

	auto position_in_map = [&](const glm::ivec2& position)
	{
		return map[0].size() > position.x && 0 <= position.x && map.size() > position.y && 0 <= position.x; 
	};

	while (next != point_start)
	{
		if (!position_in_map(next) || map[next.y][next.x] != wall)
		{
			for (int i = 0; i < move_arr.size(); i++)
			{
				glm::ivec2 check_pos = current_pos + move_arr[i];
				if (position_in_map(check_pos) && map[check_pos.y][check_pos.x] == wall)
				{
					old_move = move;
					move = move_arr[i];

					for (int j = 0; j < corner_arr.size(); j++)
					{
						if (position_in_map(current_pos + corner_arr[j]) && CheckCorner(map, current_pos, -old_move, move, corner_arr[j]))
						{
							_points.push_back(new p2t::Point(glm::dvec2((current_pos.x + corner_arr[j].x / 2.) * block_size.x,
								(current_pos.y + corner_arr[j].y / 2.) * block_size.y)));
							break;
						}
					}

					break;
				}
			}

		}
		else
		{
			map[next.y][next.x] = checked_wall;
			current_pos = next;
		}

		next = current_pos + move;
	}
}

bool NavMesh::CheckCorner(const std::vector<std::string>& map, const glm::ivec2 current_pos,
	const glm::ivec2& corner_f, const glm::ivec2& corner_s, const glm::ivec2& checking)
{
	return (checking.x * corner_f.y - checking.y * corner_f.x) * (checking.x * corner_s.y - checking.y * corner_s.x) < 0
		&& map[current_pos.y + checking.y][current_pos.x + checking.x] == '.';
}

void NavMesh::CreateNavMesh(std::vector<std::string>& map, const glm::vec2 actors_size, const glm::vec2& block_size)
{
	FillArrayOfPoints(map, block_size);

	_cdt = new p2t::CDT(_points);
	_cdt->Triangulate();

	_triangles = _cdt->GetTriangles();
	_map = _cdt->GetMap();
}
