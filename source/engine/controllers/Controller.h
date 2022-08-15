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
	//Controller(std::shared_ptr<Game::Pawn> controlledPawn, const float moveSpeed);
	Controller(const float moveSpeed);
	Controller();

	~Controller() = default;
	virtual void Move(float deltaTime);

	void SetIgnoreMoveInput(bool isIgnore);

	virtual void ChangeMoveVector(glm::vec2 inputVector);

	bool GetIsIgnoreMoveInput() { return is_ignore_move_input; }
protected:
	bool is_pause = false;
	bool is_ignore_move_input = false;

	float move_speed;

	glm::vec2 move_vector = glm::vec2(0.f);
private:
	//std::shared_ptr<Game::Pawn> controlled_pawn;
};