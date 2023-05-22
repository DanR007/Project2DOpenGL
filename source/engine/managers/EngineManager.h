#pragma once

#include <memory>



class MemoryManager;
class GameManager;
namespace Physics
{
	class PhysicsManager;
}
class RenderManager;

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
private:
	void LoadResources(char** argv);

	GameManager* _game;
	MemoryManager* _memory;
	Physics::PhysicsManager* _physics;
	RenderManager* _render;

};
