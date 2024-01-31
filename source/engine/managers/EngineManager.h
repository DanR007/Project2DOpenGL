#pragma once

#include <memory>
#include <vector>

#include "../Delegate.h"

class MemoryManager;
class GameManager;
namespace Physics
{
	class PhysicsManager;
}
class RenderManager;
class ResourcesManager;
class HUDManager;

class Delegate;
class Object;

class EngineManager
{
public:
	EngineManager(char** argv);
	~EngineManager();

	void Begin();
	void Update(const float& deltaTime);

	inline GameManager* GetWorld() { return _game; }
	inline RenderManager* GetRenderManager() { return _render; }
	inline MemoryManager* GetMemoryManager() { return _memory; }
	inline Physics::PhysicsManager* GetPhysicsManager() { return _physics; }
	inline ResourcesManager* GetResourcesManager() { return _resources; }
	inline HUDManager* GetHUDManager() { return _hud; }

	
	/// @brief метод для отложенного вызова метода/функции без аргументов
	/// @tparam M 
	/// @tparam C 
	/// @param obj объект, который будет вызывать этот метод
	/// @param method метод вызываемый
	/// @param time время до вызова
	template<class C, class M>
	void Invoke(C* obj, M method, float time)
	{
		if (obj)
		{
			Delegate new_invoke;

			_invoke_functions.push_back(std::make_pair(new_invoke, time));
			_invoke_functions.back().first.Connect(obj, method);
		}
	}

	/// @brief очищаем оставленные удаляемым объектом функции
	/// @tparam C 
	/// @param obj удаляемый объект
	void ClearFunction(const Object* obj)
	{
		for(auto it = _invoke_functions.begin(); it != _invoke_functions.end(); )
		{
			if((*it).first.compareClass(obj))
			{
				it = _invoke_functions.erase(it);
			}
			else
			{
				it++;
			}
		}
	}
private:
	void LoadResources(char** argv);

	std::vector<std::pair<Delegate, float>> _invoke_functions;

	const float c_tick_before_check_physics = 0.2f;
	float _tick_check_physics = 0.f;

	GameManager* _game = nullptr;
	MemoryManager* _memory = nullptr;
	Physics::PhysicsManager* _physics = nullptr;
	RenderManager* _render = nullptr;
	ResourcesManager* _resources = nullptr;
	HUDManager* _hud = nullptr;
};
