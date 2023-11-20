#pragma once

#include "../../../engine/default_classes/Pawn.h"

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
	
	void SetGoal(Goal* goal) { _goal = goal; }
	//developing path to cell
	void MoveTo(Cell* cell);
	//destroy goal
	void MakePathComplete();
	/// @brief может ли игрок контролировать юнит
	/// @return 
	bool CanControlling() const {return _controlling;}
protected:
	/// @brief может ли игрок контролировать его или нет
	bool _controlling = false;
	/// @brief цель куда движется юнит
	Goal* _goal = nullptr;
};