#pragma once

#include "../../engine/default_classes/Pawn.h"

struct Cell;

class Goal;

class Unit : public Game::Pawn
{
public:
	Unit(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader, const std::string& initSubtextureName,
		const glm::vec2& startPosition = glm::vec2(0.f), const glm::vec2& startSize = glm::vec2(1.f), const float& rotation = 0.f);

	Unit(Unit&& u) noexcept;
	~Unit();

	bool GetIsChoicing() const { return _is_choicing; }
	Goal* GetGoal() { return _goal; }
	glm::ivec2 GetMapPosition() const { return _map_position; }

	void SetChoicing(bool is_choicing) { _is_choicing = is_choicing; }
	void SetGoal(Goal* goal) { _goal = goal; }
	void SetMapPosition(const glm::ivec2& map_pos) { _map_position = map_pos; }

	void MoveTo(const Cell& cell);

	void PathComplete();
private:
	bool _is_choicing;

	int _hp;

	glm::ivec2 _map_position;
	Goal* _goal = nullptr;
};