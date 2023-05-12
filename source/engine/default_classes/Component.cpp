#define _USE_MATH_DEFINES
#include <cmath>

#include "../../main.h"

#include "Component.h"
#include "Actor.h"



void MovableComponent::Attach(Actor* owner)
{
	_owner = owner;
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

Component::~Component()
{
#ifdef DEBUG
	std::cout << "Destroy Component" << std::endl;
#endif
}

MovableComponent::~MovableComponent()
{
#ifdef DEBUG
	std::cout << "Destroy MovableComponent" << std::endl;
#endif
}