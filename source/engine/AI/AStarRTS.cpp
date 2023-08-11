#include "AStarRTS.h"

#include "NavMesh.h"

#include "../managers/GameManager.h"

#include "../../main.h"

#include "../../game/gameobjects/Goal.h"

#include <iostream>
#include <queue>

AStarRTS::AStarRTS()
{
	_nav_mesh = GetWorld()->GetNavMesh();
}

AStarRTS::~AStarRTS()
{
	Clear();
	_path.clear();
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

float GetLengthTurn(const glm::ivec2& dir, Cell* cell)
{
	return std::sqrtf(std::powf(cell->_cost, 2) * std::fabs(dir.x) + std::powf(cell->_cost, 2) * std::fabs(dir.y));
}

Goal* AStarRTS::DevelopPath(const glm::ivec2& start, Cell* target)
{
	Cell* trully_target = target;
	Cell* start_cell = _nav_mesh->_map[start.y][start.x];
	if (start_cell->_field_id != target->_field_id
|| target->_cost == -1 || target->_symbol != ' ')
	{
		trully_target = FindNearestCell(target, start_cell->_field_id);
	}

	Goal* goal = GetWorld()->SpawnActor<Goal>(trully_target->_position);

	PathCell* c = new PathCell(start_cell);
	c->SetDistance(trully_target->_position);
	c->CalculateCost();

	PathCell* p_cur = c;

	_close_cells.push_back(c);

	while (p_cur->GetCell() != trully_target)
	{
		p_cur = _close_cells.back();
		Cell* cur = p_cur->GetCell();

		for (short unsigned int i = 0; i < _count_move_dir; i++)
		{
			glm::ivec2 n = cur->_position + _move_dir[i];
			if (LocateInMap(n))
			{
				Cell* next;

				next = _nav_mesh->_map[n.y][n.x];
				if (CanStepInto(_move_dir[i], next, p_cur->GetCell()))
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
							new_cell->SetDistance(trully_target->_position);
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

	return goal;
}

void AStarRTS::Clear()
{
	for (PathCell* c : _close_cells)
	{
		delete c;
	}
	_close_cells.clear();

	for (PathCell* c : _open_cells)
	{
		delete c;
	}
	_open_cells.clear();
}

glm::ivec2 AStarRTS::GetNextMapGoal()
{
	if (_path.empty())
	{
		std::cout << "Path is empty" << std::endl;
		return glm::ivec2(-1, -1);
	}

	glm::ivec2 goal = _path.front(); 
	_path.erase(_path.begin()); 
	return goal;
}



void AStarRTS::CollectPath(PathCell* end_cell)
{
	_path.clear();

	PathCell* cell = end_cell;
	while (cell->GetPrev())
	{
		_path.emplace(_path.begin(), cell->GetCell()->_position);
		cell = cell->GetPrev();
	}

	Clear();
}

bool AStarRTS::LocateInMap(const glm::ivec2& pos)
{
	return _nav_mesh->_map.size() > pos.x && _nav_mesh->_map.size() > pos.y && 0 <= pos.x && 0 <= pos.y;
}

Cell* AStarRTS::FindNearestCell(Cell* target, unsigned short need_id)
{
	std::queue<glm::ivec2> q;
	std::vector<glm::ivec2> close;
	q.push(target->_position);
	while (!q.empty())
	{
		glm::ivec2 current = q.back();
		glm::ivec2 next;
		close.push_back(current);
		q.pop();
		for (unsigned short int i = 0; i < _count_move_dir; i++)
		{
			next = current + _move_dir[i];

			if (LocateInMap(next))
			{
				if (_nav_mesh->_map[next.y][next.x]->_field_id == need_id && _nav_mesh->_map[next.y][next.x]->_symbol == ' ')
				{
					return _nav_mesh->_map[next.y][next.x];
				}
				else
				{
					std::vector<glm::ivec2>::iterator it = std::find(close.begin(), close.end(), next);
					if (it == close.end())
					{
						q.push(next);
					}
				}
			}

		}
	}

#ifdef DEBUG
	std::cout << "There're zero cells with this id: " << need_id << std::endl;
#endif //DEBUG
	return nullptr;
}

PathCell* AStarRTS::GetMinCostCell()
{
	float min = FLT_MAX;
	std::vector<PathCell*>::const_iterator min_it;
	for (std::vector<PathCell*>::const_iterator it = _open_cells.begin(); it != _open_cells.end(); it++)
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

bool AStarRTS::CanStepInto(const glm::ivec2& move, Cell* next_cell, Cell* cur_cell)
{
	glm::ivec2 f = cur_cell->_position + glm::ivec2(move.x, 0);
	glm::ivec2 s = cur_cell->_position + glm::ivec2(0, move.y);
	
	return next_cell->_symbol == ' ' 
		//this condition mean that unit can't step diagonal if this split wall
		&& LocateInMap(f) && LocateInMap(s) && (_nav_mesh->_map[f.y][f.x]->_symbol == ' ' || _nav_mesh->_map[s.y][s.x]->_symbol == ' ');
}
