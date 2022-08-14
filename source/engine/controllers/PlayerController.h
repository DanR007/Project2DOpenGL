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
	PlayerController(Game::MainCharacter* controlledCharacter, const float moveSpeed);

	~PlayerController();

	virtual void Move(float deltaTime) override;
	virtual void ChangeMoveVector(glm::vec2 inputVector) override;

	void Input(GLFWwindow* currentWindow, int key, int scancode, int action, int mode);

protected:
	Game::MainCharacter* controlled_character;
};