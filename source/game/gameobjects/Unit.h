#pragma once

#include "../../engine/default_classes/Pawn.h"

struct Cell;

class Goal;

namespace Renderer
{
	class Sprite;
}

class Unit : public Pawn
{
protected:
	Unit(const std::string& initSubtextureName
		, const glm::vec2& startPosition/*lower left point*/
		, const glm::vec2& startSize = glm::vec2(1.f)
		, const uint8_t& render_layer = 1
		, const float startRotation = 0.f);
public:
	Unit(const glm::ivec2& position);

	Unit(Unit&& u) noexcept;
	virtual ~Unit();

	virtual void Update(const float& deltaTime) override;

	Goal* GetGoal() { return _goal; }

	
	void Move(const glm::vec2& position);
	
	void SetGoal(Goal* goal) { _goal = goal; }

	void MoveTo(Cell* cell);

	void PathComplete();
protected:
	Goal* _goal = nullptr;
};