#include "PlayerController.h"

#include "../managers/PhysicsManager.h"
#include "../managers/GameManager.h"

#include "../AI/NavMesh.h"

#include "../../game/gameobjects/Unit.h"
#include "../../game/gameobjects/Goal.h"

#include "../../game/gameobjects/buildings/Lumber.h"

PlayerController::PlayerController()
{ 
	SetupDefaultFunctions();

	glm::ivec2 size = GetWorld()->GetSizeMap();
	glm::vec2 block_size = GetWorld()->GetBlockSize();

	//offset is map_coord (multiply by block_size) - window_coord
	_offset = glm::vec2(float(size.x) / 2 * block_size.x, float(size.y) / 2 * block_size.y) - glm::vec2(window_size / 2);

	GetWorld()->SetOffset(_offset);

	_move_speed = 20.f;
}

PlayerController::~PlayerController()
{
	_choicing_units.~vector();
}

void PlayerController::Move(float deltaTime)
{
	_move_value = _move_vector * deltaTime * _move_speed;
	_offset += _move_value;

	if (_move_value != glm::vec2(0.f, 0.f))
	{
		GetEngine()->GetWorld()->MoveAllActors(-_move_value);
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
			if (_building)
			{
				_building->Destroy();
				_building = nullptr;
			}

			double xPos, yPos;
			glfwGetCursorPos(currentWindow, &xPos, &yPos);

			yPos = window_size.y - yPos;
			glm::ivec2 pivot_pos = GetEngine()->GetWorld()->ConvertToMapSpace(float(xPos), float(yPos));
			_building = GetEngine()->GetWorld()->SpawnActor<Lumber>(pivot_pos);
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
			glm::ivec2 map_coord = GetWorld()->ConvertToMapSpace((float)xPos, (float)yPos);

			//Print map coordinates
			std::cout << "ASCII Map coordinates (x, y): " << map_coord.x << " " << map_coord.y << std::endl;

			if (_building == nullptr)
			{
				//Print map symbol by coordinates
				if (map_coord.y >= 0 && map_coord.x >= 0)
					std::cout << GetWorld()->GetNavMesh()->GetMap()[map_coord.y][map_coord.x]->_symbol << std::endl;

				//find unit under cursor
				Unit* unit = GetEngine()->GetPhysicsManager()->GetUnitUnderCursor(glm::vec2((float)xPos, (float)yPos));

				if (_unit)
					_unit->SetSelected(_unit == unit);

				if (unit)
				{
					_unit = unit;
					_unit->SetSelected(true);
				}
			}
			else
			{
				if (_building->CanReplace())
				{
					_building->Replace();
					_building = nullptr;
				}
				else
				{
					std::cout << "Building can not replacement here" << std::endl;
				}
			}
			//CallFunction("Attack", glm::vec2(float(xPos), float(yPos)));
		}
		break;
		case GLFW_MOUSE_BUTTON_2:
		{
			double xPos, yPos;
			glfwGetCursorPos(currentWindow, &xPos, &yPos);

			yPos = window_size.y - yPos;
			glm::ivec2 map_coord = GetWorld()->ConvertToMapSpace(float(xPos), float(yPos));

			//Print map coordinates
			std::cout << "ASCII Map coordinates (x, y): " << map_coord.x << " " << map_coord.y << std::endl;

			if (_building == nullptr)
			{
				//Print map symbol by coordinates
				if (_unit && map_coord.y >= 0 && map_coord.x >= 0)
				{
					_unit->MoveTo(GetWorld()->GetMap()[map_coord.y][map_coord.x]);
				}
			}
			else
			{
				_building->Destroy();
				_building = nullptr;
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

void PlayerController::CursorMove(GLFWwindow* currentWindow, double xPos, double yPos)
{
	if (_building && !_building->GetIsReplaced())
	{
		glm::ivec2 map_space = GetEngine()->GetWorld()->ConvertToMapSpace(float(xPos), float(window_size.y - yPos)) -
			glm::ivec2(_building->GetBuildingSize().x - 1, 0);

		_building->SetMapPosition(map_space);

		glm::vec2 window_space = GetEngine()->GetWorld()->ConvertToWindowSpace(_building->GetMapPosition());

		_building->SetPosition(window_space);
	}

	glm::vec2 up = glm::vec2(0, 1), right = glm::vec2(1, 0);
	_move_vector = glm::vec2(0);
	if ((double)window_size.x - xPos < 5)
		_move_vector += right;
	if(xPos < 5)
		_move_vector -= right;
	if(yPos < 5)
		_move_vector += up;
	if ((double)window_size.y - yPos < 5)
		_move_vector -= up;
}

void PlayerController::SetupDefaultFunctions()
{
	//SetAction("MoveForward", this, &PlayerController::ChangeMoveVector);
}

