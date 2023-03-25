#include "AStarRTS.h"

#include "NavMesh.h"

#include "../managers/GameManager.h"

#include "../../main.h"

AStarRTS::AStarRTS()
{
	_nav_mesh = GetWorld()->GetNavMesh();
}


std::vector<PathCell*>::iterator Find(std::vector<PathCell*>::iterator s, std::vector<PathCell*>::iterator e, PathCell* value)
{
	std::vector<PathCell*>::iterator cur = s;
	for (; cur != e; cur++)
	{
		if (*(*cur) == *value)
		{
			break;
		}
	}
	return cur;
}

float GetLengthTurn(const glm::ivec2& dir, const Cell& cell)
{
	return std::sqrtf(std::pow(cell._cost, 2) * std::abs(dir.x) + std::pow(cell._cost, 2) * std::abs(dir.y));
}

void AStarRTS::DevelopPath(const Cell& start, const Cell& target)
{
	PathCell* c = new PathCell(start);
	c->SetDistance(target._position);
	c->CalculateCost();

	PathCell* p_cur = c;

	_close_cells.push_back(c);

	while (!_close_cells.empty() && p_cur->GetCell() != target)
	{
		p_cur = _close_cells.back();
		Cell cur = p_cur->GetCell();
		_close_cells.pop_back();
		for (short unsigned int i = 0; i < _count_move_dir; i++)
		{
			Cell next = Cell();
			next._position = cur._position + _move_dir[i];

			if (LocateInMap(next._position))
			{
				next = _nav_mesh->_map[next._position.y][next._position.x];
				if (next._cost != -1 && std::abs(next._height - p_cur->GetCell()._height) < 10.f)
				{
					PathCell* new_cell = new PathCell(next);
					auto it = Find(_open_cells.begin(), _open_cells.end(), new_cell);
					auto c_it = Find(_close_cells.begin(), _close_cells.end(), new_cell);
					float length = p_cur->GetLength() + GetLengthTurn(_move_dir[i], next);


					if (c_it == _close_cells.end())
					{
						if (it != _open_cells.end())
						{
							if ((*it)->GetLength() > length)
							{
								(*it)->SetPrev(p_cur);
								(*it)->SetLength(length);
								(*it)->SetDirection(_move_dir[i]);
								(*it)->CalculateCost();
							}
							delete new_cell;
						}
						else
						{
							new_cell->SetPrev(p_cur);
							new_cell->SetLength(length);
							new_cell->SetDistance(target._position);
							new_cell->SetDirection(_move_dir[i]);
							new_cell->CalculateCost();

							_open_cells.push_back(new_cell);
						}
					}
				}
			}
		}

		_close_cells.push_back(GetMinCostCell());
	}

	CollectPath(p_cur);
}

void AStarRTS::CollectPath(PathCell* end_cell)
{
	PathCell* cell = end_cell;
	while (cell->GetPrev())
	{
		_path.emplace(_path.begin(), cell->GetCell()._position);
		cell = cell->GetPrev();
	}
	int a = 0;
}

bool AStarRTS::LocateInMap(const glm::ivec2& pos)
{
	return _nav_mesh->_map.size() > pos.x && _nav_mesh->_map.size() > pos.y && 0 <= pos.x && 0 <= pos.y;
}

PathCell* AStarRTS::GetMinCostCell()
{
	float min = FLT_MAX;
	std::vector<PathCell*>::iterator min_it;
	for (std::vector<PathCell*>::iterator it = _open_cells.begin(); it != _open_cells.end(); it++)
	{
		if ((*it)->GetCost() < min)
		{
			min = (*it)->GetCost();
			min_it = it;
		}
	}

	PathCell* min_p = (*min_it);
	_open_cells.erase(min_it);

	return min_p;
}
