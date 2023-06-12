#pragma once
#include "../../engine/default_classes/Actor.h"

class Unit;

class Goal : public Actor
{
public:
	Goal(const std::string& initSubtextureName,
		const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation);

	Goal(const glm::ivec2& position);

	virtual void Update(const float& deltaTime) override;

	void SetUnit(Unit* unit) { _unit = unit; }
private:
	Unit* _unit = nullptr;


};