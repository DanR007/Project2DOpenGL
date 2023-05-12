#include "EngineManager.h"

#include "ResourcesManager.h"

#include <thread>

EngineManager::EngineManager(char **argv)
{
	_game = new GameManager();
	_physics = new Physics::PhysicsManager(_game);
	_render = new RenderManager();
	_memory = new MemoryManager();

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
}

void EngineManager::Begin()
{
	_game->BeginPlay();
}

void EngineManager::Update(const float& deltaTime)
{
	std::thread t1 = std::thread(&GameManager::Update, _game, std::ref(deltaTime));
	_render->Update(deltaTime);
	t1.join();
}

void EngineManager::LoadResources(char** argv)
{
	ResourcesManager::LoadAll(*argv);
}
