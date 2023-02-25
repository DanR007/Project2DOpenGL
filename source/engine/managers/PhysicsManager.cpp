#include <cmath>

#include "PhysicsManager.h"
#include "GameManager.h"

#include "../default_classes/Actor.h"

#include "../physics/Collider.h"

#include "../../main.h"

#define PI 3.141592653f

namespace Physics
{
	float VM(const glm::vec2& a, const glm::vec2& b)
	{
		return a.x * b.y - a.y * b.x;
	}
	float DOT(const glm::vec2& a, const glm::vec2& b)
	{
		return a.x * b.x + a.y * b.y;
	}

	bool PhysicsManager::CanMove(Game::Actor* firstActor, const glm::vec2& delta)
	{
		std::shared_ptr<Physics::Collider> first_collider = firstActor->GetCollider();

		for (std::shared_ptr<Game::Actor> actor : _world->_all_actors)
		{
			std::shared_ptr<Physics::Collider> second_collider = actor->GetCollider();
			if (IsBlocking(delta, first_collider, second_collider))
			{
#ifdef DEBUG
				std::cout << std::find(_world->_all_actors.begin(), _world->_all_actors.end(), actor) - _world->_all_actors.begin() <<
					" id blocking main character by position: " << std::endl;
#endif

				return false;
			}
		}
		return true;
	}

	void PhysicsManager::CheckOverlapping(std::shared_ptr<Physics::Collider> first_collider)
	{
		std::lock_guard<std::mutex> lock(first_collider->_mtx);
		first_collider->ClearOverlappingActors();

		auto it = _world->_all_actors.begin();
		for (; it != _world->_all_actors.end(); it++)
		{
			std::shared_ptr<Physics::Collider> second_collider = it->get()->GetCollider();

			if (IsOverlap(first_collider, second_collider))
			{
				//Call Delegate
				first_collider->Overlap(it->get());
				break;
			}

		}
	}

	void PhysicsManager::Update()
	{
		auto it = _world->_all_actors.begin();
		for (; it != _world->_all_actors.end(); it++)
		{
			std::shared_ptr<Physics::Collider> collider = it->get()->GetCollider();

			CheckOverlapping(collider);
		}
	}

	bool PhysicsManager::Raycast(RaycastResult& result, const glm::vec2& start, const glm::vec2& end, const ERaycastTypes& raycast_type, Game::Actor* self, bool ignore_self)
	{
		result.Clear();
		glm::vec2 half_size;
		for (std::shared_ptr<Game::Actor> actor : _world->_all_actors)
		{
			if (actor->GetCollider()->GetTraceResponseType(raycast_type) == EResponseType::ERT_Block 
				&& (!ignore_self || self != actor.get()))
			{
				half_size = actor->GetCollider()->GetSize() / 2.f;
				glm::vec2 x_axis = glm::vec2(1.f, 0.f), y_axis = glm::vec2(0.f, 1.f);
				/*
				rotate vectors:
				rot_vec.x = x * cosA - y * sinA
				rot_vec.y = x * sinA + y * cosA
				*/
				float degrees = actor->GetRotation(), rad_degrees = degrees * PI / 180.f;
				glm::vec2 rot_x = glm::vec2(x_axis.x * std::cos(rad_degrees) - x_axis.y * std::sin(rad_degrees),
					x_axis.x * std::sin(rad_degrees) + x_axis.y * std::cos(rad_degrees));
				glm::vec2 rot_y = glm::vec2(y_axis.x * std::cos(rad_degrees) - y_axis.y * std::sin(rad_degrees),
					y_axis.x * std::sin(rad_degrees) + y_axis.y * std::cos(rad_degrees));

				glm::vec2 to_center = actor->GetPosition() - start;
				glm::vec2 dir_onto_axis = glm::vec2(DOT(rot_x, end - start), DOT(rot_y, end - start));

				glm::vec2 e = glm::vec2(DOT(rot_x, to_center), DOT(rot_y, to_center));

				float t_arr[] = { 0.f,0.f,0.f,0.f };

				//check if we have zero to avoid divide by zero
				if (dir_onto_axis.x == 0)
				{
					if (-e.x - half_size.x > 0 || -e.x + half_size.x < 0)
					{
						continue;
					}
					dir_onto_axis.x = FLT_TRUE_MIN;
				}
				if (dir_onto_axis.y == 0)
				{
					if (-e.y - half_size.y > 0 || -e.y + half_size.y < 0)
					{
						continue;
					}

					dir_onto_axis.y = FLT_TRUE_MIN;
				}


				t_arr[0] = (e.x + half_size.x) / dir_onto_axis.x;
				t_arr[1] = (e.x - half_size.x) / dir_onto_axis.x;
				t_arr[2] = (e.y + half_size.y) / dir_onto_axis.y;
				t_arr[3] = (e.y - half_size.y) / dir_onto_axis.y;

				float t_min = std::max(std::min(t_arr[0], t_arr[1]), std::min(t_arr[2], t_arr[3]));
				float t_max = std::min(std::max(t_arr[0], t_arr[1]), std::max(t_arr[2], t_arr[3]));

				float dist = (t_min < 0.f) ? t_max : t_min;
				bool hit = dist > 0.f;

				if (!hit)
					continue;

				if (dist < result._distance)
				{
					//glm::vec2 normalize_dir = (end - start) / float(std::sqrt(std::pow(end.x - start.x, 2) + std::pow(end.y - start.y, 2)));

					result._hit_position = start + (end - start) * dist;
					result._normal = start - result._hit_position;
					result._hit_actor = actor.get();
					result._distance = dist;
					result._is_hit = hit;
				}
			}
		}

		return result._is_hit;
	}

	bool PhysicsManager::IsIntersection(const glm::vec2& pos_first_collider, const glm::vec2& size_first_collider,
		const glm::vec2& pos_second_collider, const glm::vec2& size_second_collider)
	{
		glm::vec2 end_first_collider = pos_first_collider + size_first_collider,
			end_second_collider = pos_second_collider + size_second_collider;
		if (pos_first_collider.x < pos_second_collider.x && end_first_collider.x > pos_second_collider.x || pos_first_collider.x >= pos_second_collider.x && pos_first_collider.x < end_second_collider.x)
		{
			return pos_first_collider.y < pos_second_collider.y&& end_first_collider.y > pos_second_collider.y || pos_first_collider.y >= pos_second_collider.y && pos_first_collider.y < end_second_collider.y;
		}
		else
		{
			return false;
		}
	}

	bool PhysicsManager::IsOverlap(std::shared_ptr<Physics::Collider> first_collider,
		std::shared_ptr<Physics::Collider> second_collider)
	{
		return IsIntersection(first_collider->GetPosition(), first_collider->GetSize(), second_collider->GetPosition(), second_collider->GetSize())
			&& first_collider->GetResponseType(second_collider->GetObjectType()) == EResponseType::ERT_Overlap;
	}

	bool PhysicsManager::IsBlocking(const glm::vec2& delta_pos,
		std::shared_ptr<Physics::Collider> first_collider,
		std::shared_ptr<Physics::Collider> second_collider)
	{
		return IsIntersection(first_collider->GetPosition() + delta_pos, first_collider->GetSize(), second_collider->GetPosition(), second_collider->GetSize())
			&& first_collider->GetResponseType(second_collider->GetObjectType()) == EResponseType::ERT_Block;
	}
}
