#pragma once

#include <memory>

#include <glm/vec2.hpp>

namespace Game
{
	class Pawn;
}

class AStar;

class Controller
{
public:
	Controller(Game::Pawn* controlledPawn, const float moveSpeed);
	Controller(const float moveSpeed);
	Controller();

	~Controller() = default;
	virtual void Move(float deltaTime);

	void SetIgnoreMoveInput(bool isIgnore);
	void SetMoveSpeed(const float move_speed) { _move_speed = move_speed; }
	virtual void ChangeMoveVector(glm::vec2 inputVector);

	bool GetIsIgnoreMoveInput() { return is_ignore_move_input; }

	inline glm::vec2 GetMoveValue() { return _move_vector; }
protected:
	bool is_pause = false;
	bool is_ignore_move_input = false;

	float _move_speed;

	glm::vec2 _move_vector = glm::vec2(0.f);
	glm::vec2 _move_value  = glm::vec2(0.f);

	Game::Pawn* _controlled_pawn;

	AStar* _a_star;
private:
	
};