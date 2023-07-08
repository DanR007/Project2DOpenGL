#include "MemoryManager.h"
#include "EngineManager.h"
#include "GameManager.h"
#include "RenderManager.h"

#include "../default_classes/Object.h"
#include "../default_classes/Actor.h"

#include "../renderer/AnimSprite.h"



#include "../../main.h"

MemoryManager::~MemoryManager()
{
	for (Object* obj : _all_objects)
	{
		delete obj;
	}
	_all_objects.clear();

	//GetEngine()->GetRenderManager()->Clear();
}

void MemoryManager::Update()
{
	std::vector<Object*>::iterator it = _all_objects.begin();
	for (; it != _all_objects.end();)
	{
		if ((*it)->GetNeedToDestroy())
		{
			if (dynamic_cast<Actor*>(*it))
			{
				GetEngine()->GetWorld()->Erase(dynamic_cast<Actor*>(*it));
			}
			if (dynamic_cast<Renderer::Sprite*>(*it))
			{
				GetEngine()->GetRenderManager()->Erase(dynamic_cast<Renderer::Sprite*>(*it));
			}

			delete (*it);
			it = _all_objects.erase(it);
		}
		else
			it++;
	}
}

void MemoryManager::AddObject(Object* obj)
{
	_all_objects.push_back(obj);
}
