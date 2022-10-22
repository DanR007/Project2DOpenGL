#include "PlayerController.h"

#include "../../game/MainCharacter.h"

#include "../managers/PhysicsManager.h"
#include "../managers/GameManager.h"

#include "../../game/weapons/WeaponComponent.h"

void PlayerController::Move(float deltaTime)
{
	_move_value = _move_vector * deltaTime * _move_speed;
	if (!is_ignore_move_input && _move_value != glm::vec2(0.f, 0.f) &&
		PhysicsManager::CanMove(_controlled_character, _controlled_character->GetPosition() + _move_value))
	{
		GameManager::MoveAllActors();
	}
}

void PlayerController::ChangeMoveVector(glm::vec2 inputVector)
{
	_move_vector += inputVector;
}

void PlayerController::InputKeyboard(GLFWwindow* currentWindow, int key, int scancode, int action, int mode)
{
	switch (action)
	{
	case GLFW_PRESS:
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(currentWindow, GLFW_TRUE);
			break;
		case GLFW_KEY_W:
			if (!is_ignore_move_input)
				ChangeMoveVector(up_vector);
			break;
		case GLFW_KEY_S:
			if (!is_ignore_move_input)
				ChangeMoveVector(up_vector * -1.f);
			break;
		case GLFW_KEY_D:
			if (!is_ignore_move_input)
				ChangeMoveVector(right_vector);
			break;
		case GLFW_KEY_A:
			if (!is_ignore_move_input)
				ChangeMoveVector(right_vector * -1.f);
			break;
		}
		break;
	case GLFW_RELEASE:
		switch (key)
		{
		case GLFW_KEY_W:
			ChangeMoveVector(up_vector * -1.f);
			break;
		case GLFW_KEY_S:
			ChangeMoveVector(up_vector);
			break;
		case GLFW_KEY_D:
			ChangeMoveVector(right_vector * -1.f);
			break;
		case GLFW_KEY_A:
			ChangeMoveVector(right_vector);
			break;
		}
		break;
	case GLFW_REPEAT:

		break;
	}
}

void PlayerController::InputMouse(GLFWwindow* currentWindow, int button, int action, int mode)
{
	switch (action)
	{
	case GLFW_PRESS:
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_1:
		{
			double xPos, yPos;
			glfwGetCursorPos(currentWindow, &xPos, &yPos);
			_controlled_character->GetWeaponComponent()->Shoot(glm::vec2(float(xPos), float(yPos)));
		}
		break;
		}
		break;
	case GLFW_RELEASE:
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_1:
		{
			double xPos, yPos;
			glfwGetCursorPos(currentWindow, &xPos, &yPos);
			_controlled_character->GetWeaponComponent()->Shoot(glm::vec2(float(xPos), float(yPos)));
		}
		break;
		}
		break;
	case GLFW_REPEAT:
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_1:
		{
			double xPos, yPos;
			glfwGetCursorPos(currentWindow, &xPos, &yPos);
			_controlled_character->GetWeaponComponent()->Shoot(glm::vec2(float(xPos), float(yPos)));
		}
		break;
		}
		break;
	}
}

void PlayerController::SetCharacter(Game::MainCharacter* controlledCharacter)
{
	_controlled_character = controlledCharacter;
}

