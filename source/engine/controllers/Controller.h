#pragma once

#include <memory>

#include <glm/vec2.hpp>

namespace Game
{
	class Pawn;
}

class Controller
{
public:
	Controller(Game::Pawn* controlledPawn, const float moveSpeed);
	Controller(const float moveSpeed);
	Controller();

	~Controller();
	virtual void Move(float deltaTime);

	void SetIgnoreMoveInput(bool isIgnore);

	virtual void ChangeMoveVector(glm::vec2 inputVector);


protected:
	bool is_pause = false;
	bool is_ignore_move_input = false;

	float move_speed;

	glm::vec2 move_vector = glm::vec2(0.f);

	Game::Pawn* controlled_pawn;
};