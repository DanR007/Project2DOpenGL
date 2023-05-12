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
public:
	Unit(const std::string& initSubtextureName,
		const glm::vec2& startPosition = glm::vec2(0.f), const glm::vec2& startSize = glm::vec2(1.f), const float& rotation = 0.f);

	Unit(Unit&& u) noexcept;
	~Unit();

	virtual void Update(const float deltaTime) override;

	bool GetIsSelected() const { return _is_selected; }
	Goal* GetGoal() { return _goal; }
	glm::ivec2 GetMapPosition() const { return _map_position; }
	
	void Move(const glm::vec2& position);

	void SetSelected(bool is_selected) { _is_selected = is_selected; }
	void SetGoal(Goal* goal) { _goal = goal; }
	void SetMapPosition(const glm::ivec2& map_pos) { _map_position = map_pos; }

	void MoveTo(const Cell& cell);

	void PathComplete();
private:
	bool _is_selected;

	int _hp;

	glm::ivec2 _map_position;
	Goal* _goal = nullptr;

	Renderer::Sprite* _selected_sprite;
};