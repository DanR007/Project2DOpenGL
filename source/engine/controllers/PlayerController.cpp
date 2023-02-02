#include "PlayerController.h"

#include "../../game/MainCharacter.h"

#include "../managers/PhysicsManager.h"
#include "../managers/GameManager.h"

#include "../../game/weapons/WeaponComponent.h"

PlayerController::PlayerController(const float speed)
{ 
	_move_speed = speed; _controlled_character = nullptr;

	SetupDefaultFunctions();
}


PlayerController::PlayerController(Game::MainCharacter* character, const float speed)
{
	_controlled_character = character;
	_move_speed = speed;

	SetupDefaultFunctions();
}

void PlayerController::Move(float deltaTime)
{
	_move_value = _move_vector * deltaTime * _move_speed;
	if (!is_ignore_move_input && _move_value != glm::vec2(0.f, 0.f) &&
		GetWorld()->GetPhysicsManager()->CanMove(_controlled_character, _move_value))
	{
		GetWorld()->MoveAllActors();
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
				CallFunction("MoveForward", up_vector);
			break;
		case GLFW_KEY_S:
			if (!is_ignore_move_input)
				CallFunction("MoveForward", up_vector * -1.f);
			break;
		case GLFW_KEY_D:
			if (!is_ignore_move_input)
				CallFunction("MoveRight", right_vector);
			break;
		case GLFW_KEY_A:
			if (!is_ignore_move_input)
				CallFunction("MoveRight", right_vector * -1.f);
			break;
		}
		break;
	case GLFW_RELEASE:
		switch (key)
		{
		case GLFW_KEY_W:
			CallFunction("MoveForward", up_vector * -1.f);
			break;
		case GLFW_KEY_S:
			CallFunction("MoveForward", up_vector);
			break;
		case GLFW_KEY_D:
			CallFunction("MoveRight", right_vector * -1.f);
			break;
		case GLFW_KEY_A:
			CallFunction("MoveRight", right_vector);
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
			CallFunction("Attack", glm::vec2(float(xPos), float(yPos)));
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
			CallFunction("Attack", glm::vec2(float(xPos), float(yPos)));
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
			CallFunction("Attack", glm::vec2(float(xPos), float(yPos)));
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

void PlayerController::SetupDefaultFunctions()
{
	SetAction("MoveForward", this, &PlayerController::ChangeMoveVector);
	SetAction("MoveRight", this, &PlayerController::ChangeMoveVector);

	if (_controlled_character->GetWeaponComponent())
	{
		SetAction("Attack", _controlled_character->GetWeaponComponent(), &WeaponComponent::Shoot);
	}
	else
	{
		std::cerr << "Can not add function Attack because haven't owner class" << std::endl;
	}
}

