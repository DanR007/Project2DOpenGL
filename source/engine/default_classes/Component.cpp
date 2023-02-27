#define _USE_MATH_DEFINES
#include <cmath>

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

void MovableComponent::SetRelativeRotation(const float new_rotation)
{
	_relative_rotation = new_rotation;
	_world_rotation = _owner->GetRotation() + _relative_rotation;

	Rotate();
}

void MovableComponent::AddRelativeRotation(const float& d_rot)
{
	_relative_rotation += d_rot;
	_world_rotation = _owner->GetRotation() + _relative_rotation;

	Rotate();
}

void MovableComponent::Rotate()
{
	/*
	rotate axis vectors:
	rot_vec.x = x * cosA - y * sinA
	rot_vec.y = x * sinA + y * cosA
	*/
	float rad_degrees = _world_rotation * M_PI / 180.f;
	_x_axis = glm::vec2(_x_axis.x * std::cos(rad_degrees) - _x_axis.y * std::sin(rad_degrees),
		_x_axis.x * std::sin(rad_degrees) + _x_axis.y * std::cos(rad_degrees));
	_y_axis = glm::vec2(_y_axis.x * std::cos(rad_degrees) - _y_axis.y * std::sin(rad_degrees),
		_y_axis.x * std::sin(rad_degrees) + _y_axis.y * std::cos(rad_degrees));
}
