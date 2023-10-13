#pragma once
#include "../../engine/default_classes/Actor.h"

class Unit;

class Goal : public Actor
{
public:
	Goal(const std::string& initSubtextureName
		, const glm::vec2& startPosition/*lower left point*/
		, const glm::vec2& startSize = glm::vec2(1.f)
		, const uint8_t& render_layer = 0
		, const float startRotation = 0.f);

	Goal(const glm::ivec2& position);

	virtual void Update(const float& deltaTime) override;

	void SetUnit(Unit* unit) { _unit = unit; }
private:
	Unit* _unit = nullptr;


};