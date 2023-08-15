#pragma once

#include "../../engine/default_classes/Actor.h"

#include "../ResourceTypes.h"

struct Cell;

class Resource : public Actor 
{
public:
	Resource(const std::string& init_sprite_name, const glm::ivec2& position, const glm::vec2& size = glm::vec2(45.f), const float& rotation = 0.f);
	virtual ~Resource();


	inline uint16_t EarnResources()
	{ 
		_resources_count--;
		if (IsEmpty())
		{
			Empty();
		}
		return 1; 
	}

	inline bool IsEmpty() const { return _resources_count == 0; }
	inline EResourceTypes GetResourceType() const { return _resource_type; }
	inline Cell* GetCell() { return _cell; }

	void SetCell(Cell* cell);
	void SetResource(const EResourceTypes& type) { _resource_type = type; }

	void Empty() { Destroy(); }
protected:
	Cell* _cell = nullptr;

	EResourceTypes _resource_type;

	uint16_t _resources_count;
	const uint16_t _max_resources_count = 15;
};