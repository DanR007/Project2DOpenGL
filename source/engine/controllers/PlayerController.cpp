#include "PlayerController.h"
#include "../managers/PhysicsManager.h"
#include "../managers/GameManager.h"

#include "../../game/gameobjects/Unit.h"
#include "../../game/gameobjects/Goal.h"

PlayerController::PlayerController()
{ 
	SetupDefaultFunctions();

	glm::ivec2 size = GetWorld()->GetSizeMap();
	glm::vec2 block_size = GetWorld()->GetBlockSize();

	//offset is map_coord (multiply by block_size) - window_coord
	_offset = glm::vec2(float(size.x) / 2 * block_size.x, float(size.y) / 2 * block_size.y) - glm::vec2(window_size / 2);

	GetWorld()->SetOffset(_offset);
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

			yPos = window_size.y - yPos;
			glm::ivec2 map_coord = GetMapCoord(xPos, yPos);

			//Print map coordinates
			std::cout << "ASCII Map coordinates (x, y): " << map_coord.x << " " << map_coord.y << std::endl;

			//Print map symbol by coordinates
			if(map_coord.y >= 0 && map_coord.x >= 0)
				std::cout << GetWorld()->GetNavMesh()->GetMap()[map_coord.y][map_coord.x]._symbol << std::endl;

			//find unit under cursor
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

			yPos = window_size.y - yPos;
			glm::ivec2 map_coord = GetMapCoord(xPos, yPos);

			//Print map coordinates
			std::cout << "ASCII Map coordinates (x, y): " << map_coord.x << " " << map_coord.y << std::endl;

			//Print map symbol by coordinates
			if (_unit && map_coord.y >= 0 && map_coord.x >= 0)
			{
				_unit->MoveTo(GetWorld()->GetNavMesh()->GetMap()[map_coord.y][map_coord.x]);
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

glm::ivec2 PlayerController::GetMapCoord(const float& xPos, const float& yPos)
{
	glm::vec2 block_size = GetWorld()->GetBlockSize();
	int size = GetWorld()->GetNavMesh()->GetMap().size();

	int yPos_map = (yPos + _offset.y) / block_size.y;
	if (yPos + _offset.y < 0 || yPos_map >= size)
		yPos_map = -1;

	int xPos_map = (xPos + _offset.x) / block_size.x;
	if (xPos + _offset.x < 0 || xPos_map >= size)
		xPos_map = -1;

	return glm::ivec2(xPos_map, yPos_map);
}

void PlayerController::SetupDefaultFunctions()
{
	//SetAction("MoveForward", this, &PlayerController::ChangeMoveVector);
}

