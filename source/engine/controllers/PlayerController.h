#pragma once

#include "Controller.h"

#include "../../main.h"

#include "../Delegate.h"

#include <string>
#include <map>
#include <iostream>

namespace Game
{
	class MainCharacter;
}

class Unit;

class PlayerController : public Controller
{
public:
	//using Controller::Controller;
	PlayerController();

	~PlayerController();

	void Move(float deltaTime) override;
	void ChangeMoveVector(glm::vec2 inputVector) override;

	void InputKeyboard(GLFWwindow* currentWindow, int key, int scancode, int action, int mode);
	void InputMouse(GLFWwindow* currentWindow, int button, int action, int mode);
	void CursorMove(GLFWwindow* currentWindow, double xPos, double yPos);

	void SetupDefaultFunctions();

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
protected:
	//offset is map_coord (multiply by block_size) - window_coord
	glm::vec2 _offset;

	Unit* _unit = nullptr;

	std::map<std::string, Delegate> _delegates_functions;

	std::vector<Unit*> _choicing_units;
};