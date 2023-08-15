#define _USE_MATH_DEFINES

#include <iostream>

#include "PhysicsManager.h"
#include "GameManager.h"

#include "../default_classes/Actor.h"

#include "../physics/Collider.h"

#include "../../main.h"

#include "../math/Math.h"

#include "../../game/gameobjects/Unit.h"


namespace Physics
{
	Collider* Physics::PhysicsManager::CreateCollider(const EObjectTypes& type, Actor* owner, const glm::ivec2 position, const glm::vec2& size)
	{
		Collider* collider = new Collider(type, owner, GetWorld()->ConvertToWindowSpace(position), size);

		_all_colliders.emplace_back(collider);

		return collider;
	}

	bool PhysicsManager::CanMove(Actor* firstActor, const glm::vec2& delta)
	{
		Physics::Collider* first_collider = firstActor->GetCollider();

		for (Actor* actor : _world->_all_actors)
		{
			Physics::Collider* second_collider = actor->GetCollider();
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

	void PhysicsManager::CheckOverlapping(Physics::Collider* first_collider)
	{
		first_collider->ClearOverlappingActors();

		auto it = _all_colliders.begin();
		for (; it != _all_colliders.end(); it++)
		{
			if ((*it) != first_collider && IsOverlap(first_collider, (*it)))
			{
				//Call Delegate
				first_collider->Overlap((*it)->GetOwner());
				break;
			}

		}
	}

	void PhysicsManager::Multithreading(int start, int end)
	{
		for (int i = start; i < end; i++)
		{
			CheckOverlapping(_all_colliders[i]);
		}
	}

	void PhysicsManager::Update()
	{
		std::thread t1 = std::thread(&Physics::PhysicsManager::Multithreading, this, 0, _all_colliders.size() / 3);
		std::thread t2 = std::thread(&Physics::PhysicsManager::Multithreading, this, _all_colliders.size() / 3, 2 * _all_colliders.size() / 3);
		std::thread t3 = std::thread(&Physics::PhysicsManager::Multithreading, this, 2 * _all_colliders.size() / 3, _all_colliders.size());

		t1.join();
		t2.join();
		t3.join();
	}

	bool PhysicsManager::Raycast(RaycastResult& result, const glm::vec2& start, const glm::vec2& end, const ERaycastTypes& raycast_type, Actor* self, bool ignore_self)
	{
		result.Clear();
		glm::vec2 half_size;
		for (Actor* actor : _world->_all_actors)
		{
			Collider* collider = actor->GetCollider();
			if (collider && collider->GetTraceResponseType(raycast_type) == EResponseType::ERT_Block 
				&& (!ignore_self || self != actor))
			{
				half_size = collider->GetSize() / 2.f;
				
				glm::vec2 x_axis = collider->GetXAxis();
				glm::vec2 y_axis = collider->GetYAxis();

				float length = Math::Length(end - start);

				glm::vec2 direction = (end - start) / length;

				glm::vec2 to_center = actor->GetPosition() - start;
				glm::vec2 dir_onto_axis = glm::vec2(Math::DOT(x_axis, direction), Math::DOT(y_axis, direction));

				glm::vec2 e = glm::vec2(Math::DOT(x_axis, to_center), Math::DOT(y_axis, to_center));

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

				if (dist < result._distance && length >= dist)
				{
					result._hit_position = start + direction * dist;
					result._normal = start - result._hit_position;
					result._hit_actor = actor;
					result._distance = dist;
					result._is_hit = hit;
				}
			}
		}

		return result._is_hit;
	}

	Unit* PhysicsManager::GetUnitUnderCursor(const glm::vec2& cursor_pos)
	{
		for (Actor* actor : _world->_all_actors)
		{
			if (IsIntersection(cursor_pos, glm::vec2(FLT_TRUE_MIN), actor->GetPosition(), actor->GetCollider()->GetSize()))
			{
				Unit* u = static_cast<Unit*>(actor);
				if (u)
					return u;
			}
		}

#ifdef DEBUG
		std::cout << "No selecting units: " << std::endl;
#endif

		return nullptr;
	}

	void PhysicsManager::Erase(Collider* collider)
	{
		_all_colliders.erase(std::find(_all_colliders.begin(), _all_colliders.end(), collider));
	}

	

	bool PhysicsManager::IsIntersection(const glm::vec2& pos_first_collider, const glm::vec2& size_first_collider,
		const glm::vec2& pos_second_collider, const glm::vec2& size_second_collider)
	{
		glm::vec2 start_first_collider = pos_first_collider,
			start_second_collider = pos_second_collider;
		glm::vec2 end_first_collider = start_first_collider + size_first_collider,
			end_second_collider = start_second_collider + size_second_collider;
		if (start_first_collider.x < start_second_collider.x && end_first_collider.x > start_second_collider.x || start_first_collider.x >= start_second_collider.x && start_first_collider.x < end_second_collider.x)
		{
			return start_first_collider.y < start_second_collider.y&& end_first_collider.y > start_second_collider.y || start_first_collider.y >= start_second_collider.y && start_first_collider.y < end_second_collider.y;
		}
		else
		{
			return false;
		}
	}

	bool PhysicsManager::IsOverlap(Physics::Collider* first_collider,
		Physics::Collider* second_collider)
	{
		return IsIntersection(first_collider->GetPosition(), first_collider->GetSize(), second_collider->GetPosition(), second_collider->GetSize())
			&& first_collider->GetResponseType(second_collider->GetObjectType()) == EResponseType::ERT_Overlap;
	}

	bool PhysicsManager::IsBlocking(const glm::vec2& delta_pos,
		Physics::Collider* first_collider,
		Physics::Collider* second_collider)
	{
		return IsIntersection(first_collider->GetPosition() + delta_pos, first_collider->GetSize(), second_collider->GetPosition(), second_collider->GetSize())
			&& first_collider->GetResponseType(second_collider->GetObjectType()) == EResponseType::ERT_Block;
	}
}
