#include "Component.h"
#include "Actor.h"

void MovableComponent::Attach(Game::Actor* owner)
{
	if (owner)
	{
		_relative_rotation = owner->GetRotation() - _world_rotation;
		_relative_position = owner->GetPosition() - _world_position;
	}
	_owner = owner;
}

void MovableComponent::Attach(Game::Actor* owner, const glm::vec2& relative_position, const float& relative_rotation)
{
	_relative_rotation = relative_rotation;
	_relative_position = relative_position;
	_owner = owner;
}
