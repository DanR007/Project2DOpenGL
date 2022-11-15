#include "AStar.h"

#include "../managers/PhysicsManager.h"

#include "../physics/Collider.h"

#include "../default_classes/Actor.h"

#include <algorithm>

glm::vec2 AStar::DevelopPath(const glm::vec2& position, const glm::vec2& target, Game::Actor* actor)
{
	glm::vec2 collider_size = actor->GetCollider()->GetSize();

	_steps = { -collider_size, glm::vec2(0.f, -collider_size.y), glm::vec2(-collider_size.x, 0.f), collider_size,
	glm::vec2(0.f, collider_size.y), glm::vec2(collider_size.x, 0.f), glm::vec2(-collider_size.x, collider_size.y), glm::vec2(collider_size.x, -collider_size.y)};
	_next_position_algorithm = Vector2(glm::vec2(0.f));
	_target = target;
	_position = position;

	Vector2 current_position, next_position = Vector2(glm::vec2(0.f));
	
	current_position = _closed_coordinates.emplace_back(Vector2(_position));
	current_position.SetCost(0.f);
	while (SquareLength(_target - _next_position_algorithm._pos) > 0.05f)
	{
		for (size_t i = 0; i < _steps.size(); i++)
		{
			next_position._pos = current_position._pos + _steps[i];
			auto position_iterator = std::find(_closed_coordinates.begin(),
				_closed_coordinates.end(), next_position);

			if (position_iterator == _closed_coordinates.end() 
				/* && GetWorld()->CanMove(actor, next_position._pos)*/
				/*&& next_position.GetCost() < current_position.GetCost() + Length(_steps[i])*/)
			{
				next_position._dir = _steps_direction[i];
				next_position.SetCost(current_position.GetCost() + Length(_steps[i])/* + DistanceInTurns(next_position._pos)*/);
				_open_coordinates.emplace_back(Vector2(next_position));
				//_open_coordinates.push_back(next_position);
			}
		}
		ChoiceSmallestCost(_next_position_algorithm);
		if (_open_coordinates.empty())
			break;
		current_position = _closed_coordinates.back();
	}

	return MakePathToPlayer(_next_position_algorithm);
}

glm::vec2 AStar::GetMoveVector()
{
	return glm::vec2();
}

void AStar::ChoiceSmallestCost(Vector2& smallest_position)
{
	float smallest_distance = FLT_MAX;

	std::vector <Vector2> ::iterator it = _open_coordinates.begin();
	std::vector <Vector2> ::iterator smallest_iterator = _open_coordinates.end();
	Vector2 old_enemy_pos;
	if (_closed_coordinates.size() > 1)
	{
		old_enemy_pos._pos = smallest_position._pos;
	}
	else
	{
		old_enemy_pos._pos = _position;
	}

	for (; it != _open_coordinates.end(); it++)
	{
		auto position_iterator = std::find(_closed_coordinates.begin(),
			_closed_coordinates.end(), *it);
		if (it->GetCost() + DistanceInTurns(it->_pos) <= smallest_distance && position_iterator == _closed_coordinates.end())
		{
			smallest_distance = it->GetCost();

			smallest_position = *it;
			smallest_iterator = it;
		}
	}


	if (smallest_iterator != _open_coordinates.end())
		_open_coordinates.erase(smallest_iterator);// удаляем чтобы не пробегать по ней снова
	_closed_coordinates.push_back(smallest_position);
}

glm::vec2 AStar::MakePathToPlayer(Vector2 pos_algorithm)
{
	Vector2 next_position_from_player;

	_path.push_back(pos_algorithm._pos);

	while (_closed_coordinates.empty() == false)
	{
		for (int i = 0; i < c_count_step; i++)
		{
			//если направление совпадает с одним из значений, то расчитываем следующую клетку
			if (pos_algorithm._dir == _steps_direction[i])
			{
				next_position_from_player._pos = pos_algorithm._pos - _steps[i];
				auto it = std::find(_closed_coordinates.begin(), _closed_coordinates.end(), next_position_from_player);
				if(it != _closed_coordinates.end())
				if (it->_pos == _position)
				{
					_closed_coordinates.erase(it);
					break;
				}
				else
				{
					next_position_from_player = *it;
					_path.push_back(next_position_from_player._pos);
					_closed_coordinates.erase(it);
					break;
				}
				/*for (std::vector <Vector2>::iterator it = _closed_coordinates.begin(); it != _closed_coordinates.end(); it++)
				{
					if (next_position_from_player._pos == _position)
					{
						_closed_coordinates.erase(it);
						break;
					}
					else
					{
						if (next_position_from_player._pos == it->_pos)
						{
							next_position_from_player._dir = it->_dir;
							_closed_coordinates.erase(it);
							_path.push_back(next_position_from_player._pos);
							break;
						}
					}
				}*/

			}
		}
		pos_algorithm = _path.back();
	}
	_open_coordinates.clear();
	_closed_coordinates.clear();
	return next_position_from_player._pos;
}
