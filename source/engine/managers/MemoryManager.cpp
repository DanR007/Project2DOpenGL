#include "MemoryManager.h"
#include "EngineManager.h"
#include "GameManager.h"
#include "RenderManager.h"

#include "../default_classes/Object.h"
#include "../default_classes/Actor.h"

#include "../renderer/AnimSprite.h"



#include "../../main.h"

void MemoryManager::Update()
{
	std::vector<std::shared_ptr<Object>>::iterator it = _all_objects.begin();
	for (; it != _all_objects.end();)
	{
		if ((*it)->GetNeedToDestroy())
		{
			if (std::dynamic_pointer_cast<Actor>(*it))
			{
				GetEngine()->GetWorld()->Erase(std::dynamic_pointer_cast<Actor>(*it));
			}
			if (std::dynamic_pointer_cast<Renderer::Sprite>(*it))
			{
				GetEngine()->GetRenderManager()->Erase(dynamic_cast<Renderer::Sprite*>((*it).get()));
			}
			it = _all_objects.erase(it);
		}
		else
			it++;
	}
}

void MemoryManager::AddObject(std::shared_ptr<Object> obj)
{
	_all_objects.push_back(obj);
}
