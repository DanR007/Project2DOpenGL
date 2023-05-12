#pragma once

#include <memory>

#include "GameManager.h"
#include "PhysicsManager.h"
#include "MemoryManager.h"
#include "RenderManager.h"

class EngineManager
{
public:
	EngineManager(char** argv);
	~EngineManager();

	void Begin();
	void Update(const float& deltaTime);

	GameManager* GetWorld() { return _game; }
	RenderManager* GetRenderManager() { return _render; }
private:
	void LoadResources(char** argv);

	GameManager* _game;
	MemoryManager* _memory;
	Physics::PhysicsManager* _physics;
	RenderManager* _render;

};
