#include "EngineManager.h"

#include "ResourcesManager.h"
#include "GameManager.h"
#include "PhysicsManager.h"
#include "MemoryManager.h"
#include "RenderManager.h"

#include <thread>

EngineManager::EngineManager(char **argv)
{
	_game = new GameManager();
	_physics = new Physics::PhysicsManager(_game);
	_render = new RenderManager();
	_memory = new MemoryManager();
	_resources = new ResourcesManager();

	LoadResources(argv);
}

EngineManager::~EngineManager()
{
	if (_game)
	{
		delete _game;
		_game = nullptr;
	}
	if (_physics)
	{
		delete _physics;
		_physics = nullptr;
	}
	if (_render)
	{
		delete _render;
		_render = nullptr;
	}
	if (_memory)
	{
		delete _memory;
		_memory = nullptr;
	}
	if (_resources)
	{
		delete _resources;
		_resources = nullptr;
	}
}

void EngineManager::Begin()
{
	if(_game)
		_game->BeginPlay();
}

void EngineManager::Update(const float& deltaTime)
{
	_tick_check_physics += deltaTime;

	{
		_render->Update(deltaTime);
		std::thread t1 = std::thread(&GameManager::Update, _game, std::ref(deltaTime));
		t1.join();
	}
	_memory->Update();
}

void EngineManager::LoadResources(char** argv)
{
	_resources->LoadAll(*argv);
}