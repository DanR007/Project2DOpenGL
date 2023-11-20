#pragma once

#include "Controller.h"

#include "../../main.h"

#include "../Delegate.h"

#include "../../game/gameobjects/static/resources/ResourceTypes.h"

#include <string>
#include <map>
#include <iostream>

namespace Game
{
	class MainCharacter;
}

class Unit;
class Building;

class Widget;
class Text;

struct ResourceStock
{
	ResourceStock(Text* text, const size_t& count, const EResourceTypes& type):
		_text(text), _count(count), _type(type)
	{
		
	}

	bool operator==(const ResourceStock& res)
	{
		return _type == res._type;
	}
	bool operator==(const EResourceTypes& res)
	{
		return _type == res;
	}

	Text* _text;
	size_t _count;
	EResourceTypes _type;
};

class PlayerController : public Controller
{
public:
	//using Controller::Controller;
	PlayerController(uint8_t id);
	PlayerController(uint8_t id, Widget* widget);

	virtual ~PlayerController();

	/// @brief перемещение камеры (курсором)
	/// @param deltaTime 
	void Move(float deltaTime) override;
	/// @brief изменение вектора перемещения камеры
	/// @param inputVector 
	void ChangeMoveVector(glm::vec2 inputVector) override;

	/// @brief ввод с клавиатуры
	/// @param currentWindow текущее окно, из которого был вызов
	/// @param key клавиша
	/// @param scancode 
	/// @param action действие (зажатие, отпускание или клик)
	/// @param mode 
	void InputKeyboard(GLFWwindow* currentWindow, int key, int scancode, int action, int mode);
	/// @brief ввод с мыши
	/// @param currentWindow 
	/// @param button 
	/// @param action 
	/// @param mode 
	void InputMouse(GLFWwindow* currentWindow, int button, int action, int mode);
	/// @brief движение курсора
	/// @param currentWindow 
	/// @param xPos 
	/// @param yPos 
	void CursorMove(GLFWwindow* currentWindow, double xPos, double yPos);

	/// @brief выставление стандартных делегатов
	void SetupDefaultFunctions();

	void SetWidget(Widget* widget);

	inline Widget* GetWidget() { return _widget; }

	template<class C, class M>
	void SetAction(const std::string& name, C* own_class, M method)
	{
		if (own_class)
		{
			Delegate new_delegate;

			_delegates_functions.emplace(name, new_delegate);
			_delegates_functions[name].Connect(own_class, method);
		}
		else
		{
			std::cerr << "Own class by function: " + name + " not valid" << std::endl;
		}
	}
	template<typename T>
	void CallFunction(const std::string& name_function, T argument)
	{
		std::map<std::string, Delegate>::iterator it = _delegates_functions.find(name_function);

		if (it == _delegates_functions.end())
		{
			std::cerr << "PlayerController can not find function by name: " + name_function << std::endl;
			return;
		}

		it->second(argument);
	}

	void AddResource(const EResourceTypes& type, const size_t& count);
	void MinusResources(const std::vector<std::pair<EResourceTypes, size_t>>& resources);
	
protected:
	/// @brief достаточно ли ресурсов на действие
	/// @param resources 
	/// @return 
	bool EnoughResources(const std::vector<std::pair<EResourceTypes, size_t>>& resources);

	/// @brief создание здания
	/// @tparam T тип здания
	/// @param position позиция курсора в окне
	template<typename T>
	void CreateBuilding(const glm::vec2& position);
	/// @brief загрузка интерфейса
	void ConfigureUI();
	/// @brief выбор юнита
	/// @param mouse_pos позиция курсора мыши
	void ChooseUnit(const glm::vec2& mouse_pos);
	/// @brief Нажатие на кнопку
	/// @param mouse_pos позиция курсора
	void ClickButton(const glm::vec2& mouse_pos);
	/// @brief Нажатие на мышь
	/// @param mouse_pos позиция курсора
	void Click(const glm::vec2& mouse_pos);

	//offset is map_coord (multiply by block_size) - window_coord
	glm::vec2 _offset;

	Unit* _unit = nullptr;
	Building* _building = nullptr;

	uint8_t _id;

	std::map<std::string, Delegate> _delegates_functions;

	std::vector<Unit*> _choicing_units;

	std::vector<ResourceStock> _resource_stocks;

	Widget* _widget;
};