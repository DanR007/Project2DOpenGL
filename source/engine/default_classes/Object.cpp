#define _USE_MATH_DEFINES
#include <cmath>

#include "Object.h"

#include "../../main.h"

#include "../managers/EngineManager.h"
#include "../managers/MemoryManager.h"

Object::Object()
{
	_need_to_destroy = false;

	GetEngine()->GetMemoryManager()->AddObject(this);
}

Object::~Object()
{
#ifdef DEBUG
	std::cout << "Destroy Object" << std::endl;
#endif
}
void Object::Rotate()
{
	/*
	rotate axis vectors:
	rot_vec.x = x * cosA - y * sinA
	rot_vec.y = x * sinA + y * cosA
	*/
	float rad_degrees = _rotation * M_PI / 180.f;
	_x_axis = glm::vec2(_x_axis.x * std::cos(rad_degrees) - _x_axis.y * std::sin(rad_degrees),
		_x_axis.x * std::sin(rad_degrees) + _x_axis.y * std::cos(rad_degrees));
	_y_axis = glm::vec2(_y_axis.x * std::cos(rad_degrees) - _y_axis.y * std::sin(rad_degrees),
		_y_axis.x * std::sin(rad_degrees) + _y_axis.y * std::cos(rad_degrees));
}
void Object::SetPosition(const glm::vec2& new_position)
{
	_world_position = new_position;

	for (Object* obj : _attached_objects)
	{
		if(obj)
		{
			obj->SetPosition(new_position);
		}
	}
}
void Object::SetSize(const glm::vec2& new_size)
{
	_size = new_size;
	for (Object* obj : _attached_objects)
	{
		if(obj)
		{
			obj->SetSize(new_size);
		}
	}
}
void Object::SetRotation(const float& new_rotation)
{
	_rotation = new_rotation;
	for (Object* obj : _attached_objects)
	{
		if(obj)
		{
			obj->SetRotation(new_rotation);
		}
	}
}
void Object::SetRelativePosition(const glm::vec2& new_position)
{
	glm::vec2 d_pos = new_position - _relative_position;
	_relative_position = new_position;
	for (Object* obj : _attached_objects)
	{
		if(obj)
		{
			obj->SetRelativePosition(new_position);
		}
	}
}
void Object::AddWorldPosition(const glm::vec2& d_pos)
{
	_world_position += d_pos;

	for (Object* obj : _attached_objects)
	{
		if(obj)
		{
			obj->AddWorldPosition(d_pos);
		}
	}
}
void Object::AddWorldRotation(const float& d_rot)
{
	_rotation += d_rot;
	for (Object* obj : _attached_objects)
	{
		if(obj)
		{
			obj->AddWorldRotation(d_rot);
		}
	}
}
