#pragma once

#include "Controller.h"

#include "../../main.h"

namespace Game
{
	class MainCharacter;
}

class PlayerController : public Controller
{
public:

	//using Controller::Controller;
	//PlayerController(const float moveSpeed);
	PlayerController(const float speed) { move_speed = speed; }
	~PlayerController() = default;

	virtual void Move(float deltaTime) override;
	virtual void ChangeMoveVector(glm::vec2 inputVector) override;

	void Input(GLFWwindow* currentWindow, int key, int scancode, int action, int mode);

	void SetCharacter(Game::MainCharacter* controlledCharacter);

protected:
	std::shared_ptr<Game::MainCharacter> controlled_character;
};