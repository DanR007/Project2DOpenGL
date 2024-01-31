#include "EngineManager.h"

#include "ResourcesManager.h"
#include "GameManager.h"
#include "PhysicsManager.h"
#include "MemoryManager.h"
#include "RenderManager.h"
#include "HUDManager.h"

#include <thread>

EngineManager::EngineManager(char **argv)
{
	_game = new GameManager();
	_physics = new Physics::PhysicsManager(_game);
	_render = new RenderManager();
	_memory = new MemoryManager();
	_resources = new ResourcesManager();
	_hud = new HUDManager();

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
	if (_hud)
	{
		delete _hud;
		_hud = nullptr;
	}
}

void EngineManager::Begin()
{
#ifdef DEBUG
	std::cout << "Begin game" << std::endl;
#endif
	if(_game)
	{
		_game->BeginPlay();
	}

	Invoke((Object*)GetWorld()->GetActors()[0], &Object::Destroy, 5.f);
	GetWorld()->GetActors()[0]->Destroy();
}

void EngineManager::Update(const float& deltaTime)
{
	_tick_check_physics += deltaTime;

	{
		/*std::thread t1 = std::thread(&GameManager::Update, _game, std::ref(deltaTime));
		_render->Update(deltaTime);
		t1.join();
*/
		//смотрим вышло ли время на вызов какой-то функции
		for(auto it = _invoke_functions.begin(); it != _invoke_functions.end(); )
		{
			(*it).second -= deltaTime;
			if((*it).second <= 0)
			{
				(*it).first.operator()();
				it = _invoke_functions.erase(it);
			}
			else
			{
				it++;
			}
		}
	}
	_memory->Update();
}

void EngineManager::LoadResources(char** argv)
{
	_resources->LoadAll(*argv);
}
