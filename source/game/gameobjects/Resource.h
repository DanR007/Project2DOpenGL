#pragma once

#include "../../engine/default_classes/Actor.h"

#include "../ResourceTypes.h"

class Resource : public Actor 
{
public:
	Resource(const std::string& init_sprite_name, const glm::ivec2& position, const glm::vec2& size = glm::vec2(45.f), const float& rotation = 0.f);
	~Resource();


	uint16_t GetResources() 
	{ 
		_resources_count--;
		return 1; 
	}

	void SetCell(Cell* cell) { _cell = cell; }
protected:
	Cell* _cell;

	EResorceTypes _resource_type;

	uint16_t _resources_count;
	const uint16_t _max_resources_count = 100;
};