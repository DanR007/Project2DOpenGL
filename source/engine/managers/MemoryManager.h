#pragma once 

#include <memory>
#include <vector>

class Object;

class MemoryManager
{
public:
	void Update();

	void AddObject(std::shared_ptr<Object> obj);
private:
	std::vector<std::shared_ptr<Object>> _all_objects;
};