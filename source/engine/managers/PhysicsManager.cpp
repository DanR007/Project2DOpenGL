#include "PhysicsManager.h"
#include "GameManager.h"

#include "../default_classes/Actor.h"

#include "../physics/Collider.h"

#include "../../main.h"

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

