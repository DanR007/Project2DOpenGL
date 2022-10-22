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
	PlayerController(const float speed) { _move_speed = speed; _controlled_character = nullptr; }
	PlayerController(Game::MainCharacter* character, const float speed) 
	{
		_move_speed = speed; _controlled_character = character;
	}

	~PlayerController() = default;

	void Move(float deltaTime) override;
	void ChangeMoveVector(glm::vec2 inputVector) override;

	void InputKeyboard(GLFWwindow* currentWindow, int key, int scancode, int action, int mode);
	void InputMouse(GLFWwindow* currentWindow, int button, int action, int mode);

	void SetCharacter(Game::MainCharacter* controlledCharacter);

protected:
	Game::MainCharacter* _controlled_character;
};