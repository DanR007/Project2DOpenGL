#include "PlayerController.h"
#include "../managers/PhysicsManager.h"
#include "../managers/GameManager.h"

#include "../../game/gameobjects/Unit.h"

PlayerController::PlayerController()
{ 
	SetupDefaultFunctions();

	glm::ivec2 size = GetWorld()->GetSizeMap();
	glm::vec2 block_size = GetWorld()->GetBlockSize();

	//offset is map_coord (multiply by block_size) - window_coord
	_offset = glm::vec2(window_size / 2) - glm::vec2(float(size.x) / 2 * block_size.x, float(size.y) / 2 * block_size.y);
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

			glm::vec2 block_size = GetWorld()->GetBlockSize();

			yPos = window_size.y - yPos - 2 * _offset.y;
			xPos = xPos - 2 * _offset.x;

			//Print map coordinates
			std::cout << (int)(xPos / block_size.x) << " " << (int)(yPos / block_size.y) << std::endl;

			int size = GetWorld()->GetNavMesh()->GetMap().size();
			//Print map symbol by coordinates
			if((int)(xPos / block_size.x) < size && size > (int)(yPos / block_size.y) && (int)(yPos / block_size.y) >= 0 && (int)(xPos / block_size.x) >= 0)
				std::cout << GetWorld()->GetNavMesh()->GetMap()[(int)(xPos / block_size.x)][(int)(yPos / block_size.y)]._symbol << std::endl;

			_unit = GetWorld()->GetPhysicsManager()->GetUnitUnderCursor(glm::vec2(xPos, yPos));
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

			glm::vec2 block_size = GetWorld()->GetBlockSize();

			yPos = yPos  - _offset.y;
			xPos = xPos + _offset.x;

			//Print map coordinates
			std::cout << (int)(xPos / block_size.x) << " " << (int)(yPos / block_size.y) << std::endl;

			int size = GetWorld()->GetNavMesh()->GetMap().size();
			//Print map symbol by coordinates
			if ((int)(xPos / block_size.x) < size && size > (int)(yPos / block_size.y) && (int)(yPos / block_size.y) >= 0 && (int)(xPos / block_size.x) >= 0)
			{
				std::cout << GetWorld()->GetNavMesh()->GetMap()[(int)(xPos / block_size.x)][(int)(yPos / block_size.y)]._symbol << std::endl;
				_unit->MoveTo(GetWorld()->GetNavMesh()->GetMap()[yPos / block_size.y][xPos / block_size.x]);
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

