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
	Controller(std::shared_ptr<Game::Pawn> controlledCharacter);

	virtual void Move();

	virtual void SetIgnoreMoveInput(bool isIgnore);

	virtual void ChangeMoveVector(glm::vec2 inputVector);

private:
	bool is_pause = false;
	bool is_ignore_move_input = false;

	glm::vec2 move_vector;

	std::shared_ptr<Game::Pawn> controlled_character;
};