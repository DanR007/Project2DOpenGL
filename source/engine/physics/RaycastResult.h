#pragma once

#ifndef __linux__
	#define FLT_MAX FLT_MAX
#else
	#define FLT_MAX __FLT_MAX__
#endif

#include <glm/vec2.hpp>

class Actor;


struct RaycastResult
{
	void Clear()
	{
		_is_hit = false;
		_distance = FLT_MAX;
		_hit_position = glm::vec2(0);
		_normal = glm::vec2(0);
		_hit_actor = nullptr;
	}

	bool _is_hit = false;
	float _distance = FLT_MAX;
	glm::vec2 _hit_position = glm::vec2(0);
	glm::vec2 _normal = glm::vec2(0);
	Actor* _hit_actor = nullptr;
};