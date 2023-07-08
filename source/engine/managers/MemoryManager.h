#pragma once 

#include <memory>
#include <vector>

class Object;

class MemoryManager
{
public:
	~MemoryManager();
	void Update();

	void AddObject(Object* obj);
private:
	std::vector<Object*> _all_objects;
};