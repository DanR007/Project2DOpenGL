#include "PlayerController.h"

#include "../managers/PhysicsManager.h"
#include "../managers/GameManager.h"
#include "../managers/HUDManager.h"
#include "../managers/RenderManager.h"

#include "../AI/NavMesh.h"

#include "../../game/gameobjects/units/Unit.h"
#include "../../game/gameobjects/Goal.h"

#include "../../game/gameobjects/static/buildings/Lumber.h"
#include "../../game/gameobjects/static/buildings/Quarry.h"
#include "../../game/gameobjects/static/buildings/Barracks.h"

#include "../UI/Widget.h"
#include "../UI/Text.h"
#include "../UI/Panel.h"
#include "../UI/Button.h"
#include "../UI/Image.h"
#include "../UI/ProgressBar.h"

#ifdef __linux__
#include <algorithm>
#endif

#define RESOURCE_FORMAT(res, count) (res + ":" + count)

std::map<EResourceTypes, std::string> _resource_names =
{
	{EResourceTypes::ERT_Wood, "Wood"},
	{EResourceTypes::ERT_Stone, "Stone"},
	{EResourceTypes::ERT_Gold, "Gold"}
};

PlayerController::PlayerController(uint8_t id) : _id(id)
{ 
	SetupDefaultFunctions();

	glm::ivec2 size = GetWorld()->GetSizeMap();
	glm::vec2 block_size = GetWorld()->GetBlockSize();

	//offset is map_coord (multiply by block_size) - window_coord
	_offset = glm::vec2(float(size.x) / 2 * block_size.x, float(size.y) / 2 * block_size.y) - glm::vec2(window_size / 2);

	GetWorld()->SetOffset(_offset);

	_move_speed = 20.f;

	_widget = GetEngine()->GetHUDManager()->CreateWidget();

	ConfigureUI();
}

PlayerController::PlayerController(uint8_t id, Widget* widget): _widget(widget), _id(id)
{
	SetupDefaultFunctions();

	glm::ivec2 size = GetWorld()->GetSizeMap();
	glm::vec2 block_size = GetWorld()->GetBlockSize();

	//offset is map_coord (multiply by block_size) - window_coord
	_offset = glm::vec2(float(size.x) / 2 * block_size.x, float(size.y) / 2 * block_size.y) - glm::vec2(window_size / 2);

	GetWorld()->SetOffset(_offset);

	_move_speed = 20.f;

	ConfigureUI();
}

PlayerController::~PlayerController()
{
	_choicing_units.~vector();
}

template<typename T>
void PlayerController::CreateBuilding(const glm::vec2& position)
{
	glm::ivec2 pivot_pos = GetEngine()->GetWorld()->ConvertToMapSpace(position)/*чтобы здание появилось четко под курсором*/;
	_building = GetEngine()->GetWorld()->SpawnActor<T>(pivot_pos);
	_building->SetPlayerID(_id);
	_building->SetMapPosition(pivot_pos -
	glm::ivec2(_building->GetBuildingSize().x - 1, 0));
	glm::vec2 window_space = GetEngine()->GetWorld()->ConvertToWindowSpace(_building->GetMapPosition());
	_building->SetPosition(window_space);
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

void PlayerController::InputKeyboard(GLFWwindow* currentWindow
									, int key
									, int scancode
									, int action
									, int mode)
{
	switch (action)
	{
	case GLFW_PRESS:
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			{
				glfwSetWindowShouldClose(currentWindow, GLFW_TRUE);
			}
			break;
		case GLFW_KEY_W:
			{
				if (_building)
				{
					_building->Destroy();
					_building = nullptr;
				}

				double xPos, yPos;
				glfwGetCursorPos(currentWindow, &xPos, &yPos);

				yPos = window_size.y - yPos;
				CreateBuilding<Lumber>(glm::vec2(xPos, yPos));
			}
			break;
		case GLFW_KEY_S:
			{
				if (_building)
				{
					_building->Destroy();
					_building = nullptr;
				}

				double xPos, yPos;
				glfwGetCursorPos(currentWindow, &xPos, &yPos);

				yPos = window_size.y - yPos;
				CreateBuilding<Quarry>(glm::vec2(xPos, yPos));
			}
			break;
		case GLFW_KEY_B:
			{
				if (_building)
				{
					_building->Destroy();
					_building = nullptr;
				}

				double xPos, yPos;
				glfwGetCursorPos(currentWindow, &xPos, &yPos);

				yPos = window_size.y - yPos;
				CreateBuilding<Barracks>(glm::vec2(xPos, yPos));
			}
			break;
		}
	}
	break;
	case GLFW_RELEASE:
	{
		switch (key)
		{

		}
	}
	break;
	case GLFW_REPEAT:
		{

		}
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
				if (GetWorld()->GetNavMesh()->InMap(map_coord))
				{
#ifdef DEBUG
				//Print map symbol by coordinates
					std::cout << GetWorld()->GetNavMesh()->GetMap()[map_coord.y][map_coord.x]->_symbol << std::endl;
#endif //DEBUG
				}

				Click(glm::vec2(xPos, yPos));
			}
			else
			{
				if (EnoughResources(_building->GetCost()) && _building->CanReplace())
				{
					MinusResources(_building->GetCost());
					_building->Replace();
					_building = nullptr;
				}
				else
				{
					std::cout << "Building can not replacement here" << std::endl;
				}
			}
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
				if (_unit && GetWorld()->GetNavMesh()->InMap(map_coord))
				{
					_unit->MoveTo(GetWorld()->GetMap()[map_coord.y][map_coord.x]);
				}
				else
				{

				}
			}
			else
			{
				_building->Destroy();
				_building = nullptr;
			}
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
			/*отнимаем один чтобы позиция на карте была чётко под курсором, а не левее*/

		if(GetEngine()->GetWorld()->GetNavMesh()->InMap(map_space))
		{
			_building->SetMapPosition(map_space);

			glm::vec2 window_space = GetEngine()->GetWorld()->ConvertToWindowSpace(_building->GetMapPosition());

			_building->SetPosition(window_space);
		}
		else
		{
#ifdef DEBUG
	std::cout << "Cursor not in map space" << std::endl;
#endif
		}
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

void PlayerController::SetWidget(Widget* widget)
{
	_widget = widget;
}

void PlayerController::AddResource(const EResourceTypes& type, const size_t& count)
{
	auto it = std::find(_resource_stocks.begin(), _resource_stocks.end(), ResourceStock(nullptr, count, type));
	it->_count += count;
	it->_text->SetText(RESOURCE_FORMAT(_resource_names[type], std::to_string(it->_count)));
}

void PlayerController::MinusResources(const std::vector<std::pair<EResourceTypes, size_t>>& resources)
{
	for (ResourceStock& res : _resource_stocks)
	{
		for (std::pair<EResourceTypes, size_t> resource : resources)
		{
			//
			if (res == resource.first)
			{
				res._count -= resource.second;
				res._text->SetText(RESOURCE_FORMAT(_resource_names[res._type], std::to_string(res._count)));
			}
		}
	}
}

bool PlayerController::EnoughResources(const std::vector<std::pair<EResourceTypes, size_t>>& resources)
{
	for (ResourceStock res : _resource_stocks)
	{
		for (std::pair<EResourceTypes, size_t> resource : resources)
		{
			if(res == resource.first && res._count < resource.second)
				return false;
		}
	}

	return true;
}

void PlayerController::ConfigureUI()
{

	/*блок отображения ресурсов*/
	_widget->AddElement<Panel>(glm::vec2(0, window_size.y / 6.f * 5.f), glm::vec2(window_size.x, window_size.y / 6.f));

	glm::vec2 position = glm::vec2(20.f, window_size.y - 45.f);
	glm::vec2 size_symbol(25.f);
	int start_wood = 10, start_stone = 0, start_gold = 0;
	_resource_stocks.emplace_back(ResourceStock(
		_widget->AddElement<Text>(position, size_symbol), start_wood, EResourceTypes::ERT_Wood)
	)._text->SetText(RESOURCE_FORMAT(_resource_names[EResourceTypes::ERT_Wood], std::to_string(10)));
	_resource_stocks.emplace_back(ResourceStock(
		_widget->AddElement<Text>(glm::vec2(position.x * 20, position.y), size_symbol), start_stone, EResourceTypes::ERT_Stone)
	)._text->SetText(RESOURCE_FORMAT(_resource_names[EResourceTypes::ERT_Stone], std::to_string(0)));
	_resource_stocks.emplace_back(ResourceStock(
		_widget->AddElement<Text>(glm::vec2(position.x, position.y - size_symbol.y * 2.f), size_symbol), start_gold, EResourceTypes::ERT_Gold)
	)._text->SetText(RESOURCE_FORMAT(_resource_names[EResourceTypes::ERT_Gold], std::to_string(0)));
	/*конец инициализации отображения ресурсов */


	_widget->AddElement<Panel>(glm::vec2(0), glm::vec2(window_size.x, window_size.y / 6.f));

	ProgressBar* progress_bar = _widget->AddElement<ProgressBar>(glm::vec2(20.f), glm::vec2(400, 50));
	progress_bar->SetEmptySpriteByName("emptyProgressBar");
	progress_bar->SetFullSpriteByName("fullProgressBar");
	progress_bar->SetPercentage(0.5f);
	progress_bar->SetRender(false);
}

void PlayerController::ChooseUnit(const glm::vec2 &mouse_pos)
{
	//find unit under cursor
	Unit* unit = GetEngine()->GetPhysicsManager()->GetUnitUnderCursor(mouse_pos);
	if (_unit)
	{
		_unit->SetSelected(_unit == unit);
	}

	if (unit && unit->GetID() == _id)
	{
		_unit = unit;
		_unit->SetSelected(true);
	}
	else
	{
		_unit = nullptr;
	}
}

void PlayerController::ClickButton(const glm::vec2 &mouse_pos)
{
	//find button under cursor
	GetEngine()->GetPhysicsManager()->CheckClickButton(mouse_pos);
}

void PlayerController::Click(const glm::vec2 &mouse_pos)
{
	ClickButton(mouse_pos);
	ChooseUnit(mouse_pos);
}
