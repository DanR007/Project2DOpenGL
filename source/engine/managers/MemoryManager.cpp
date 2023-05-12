#include "MemoryManager.h"

#include "../default_classes/Object.h"

void MemoryManager::Update()
{
	std::vector<std::shared_ptr<Object>>::iterator it = _all_objects.begin();
	for (; it != _all_objects.end();)
	{
		if ((*it)->GetNeedToDestroy())
		{
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
