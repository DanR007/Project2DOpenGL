#include "PlayerController.h"
#include "../managers/PhysicsManager.h"
#include "../managers/GameManager.h"

#include "../../game/gameobjects/Unit.h"

PlayerController::PlayerController()
{ 
	SetupDefaultFunctions();
}

void PlayerController::Move(float deltaTime)
{
	_move_value = _move_vector * deltaTime * _move_speed;
	if (_move_value != glm::vec2(0.f, 0.f))
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
			
			break;
		case GLFW_KEY_S:
			
			break;
		case GLFW_KEY_D:
			
			break;
		case GLFW_KEY_A:
			
			break;
		}
		break;
	case GLFW_RELEASE:
		switch (key)
		{
		case GLFW_KEY_W:
			
			break;
		case GLFW_KEY_S:
			
			break;
		case GLFW_KEY_D:
		
			break;
		case GLFW_KEY_A:
			
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
			std::cout << (int)(xPos / 45) << " " << (int)(yPos / 45) << std::endl;
			int size = GetWorld()->GetNavMesh()->GetMap().size();
			if((int)(xPos / 45) < size && size > (int)(yPos / 45) && (int)(yPos / 45) >= 0 && (int)(xPos / 45) >= 0)
				std::cout << GetWorld()->GetNavMesh()->GetMap()[(int)(xPos / 45)][(int)(yPos / 45)]._symbol << std::endl;
			_unit = GetWorld()->GetPhysicsManager()->GetUnitUnderCursor(glm::vec2(xPos, window_size.y - yPos));
			if (_unit)
			{
				_unit->SetChoicing(true);
			}
			//CallFunction("Attack", glm::vec2(float(xPos), float(yPos)));
		}
		break;
		case GLFW_MOUSE_BUTTON_2:
		{
			double xPos, yPos;
			glfwGetCursorPos(currentWindow, &xPos, &yPos);
			std::cout << (int)(xPos / 45) << " " << (int)(yPos / 45) << std::endl;
			int size = GetWorld()->GetNavMesh()->GetMap().size();
			if (_unit && (int)(xPos / 45) < size && size > (int)(yPos / 45) && (int)(yPos / 45) >= 0 && (int)(xPos / 45) >= 0)
			{
				_unit->MoveTo(GetWorld()->GetNavMesh()->GetMap()[yPos / 45][xPos / 45]);
				std::cout << GetWorld()->GetNavMesh()->GetMap()[(int)(yPos / 45)][(int)(xPos / 45)]._symbol << std::endl;
			}
			
			//CallFunction("Attack", glm::vec2(float(xPos), float(yPos)));
		}
		break;
		}
		break;
	case GLFW_RELEASE:
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_1:
		{
			
		}
		break;
		}
		break;
	case GLFW_REPEAT:
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_1:
		{
			
		}
		break;
		}
		break;
	}
}

void PlayerController::SetupDefaultFunctions()
{
	//SetAction("MoveForward", this, &PlayerController::ChangeMoveVector);
}

