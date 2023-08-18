#pragma once

#include <memory>



class MemoryManager;
class GameManager;
namespace Physics
{
	class PhysicsManager;
}
class RenderManager;
class ResourcesManager;
class HUDManager;

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
private:
	const float c_tick_before_check_physics = 0.2f;
	float _tick_check_physics = 0.f;

	void LoadResources(char** argv);

	GameManager* _game = nullptr;
	MemoryManager* _memory = nullptr;
	Physics::PhysicsManager* _physics = nullptr;
	RenderManager* _render = nullptr;
	ResourcesManager* _resources = nullptr;
	HUDManager* _hud = nullptr;
};
