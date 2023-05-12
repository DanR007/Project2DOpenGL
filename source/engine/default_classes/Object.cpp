#include "Object.h"

#include "../../main.h"

Object::Object()
{
	_need_to_destroy = false;
}

Object::~Object()
{
#ifdef DEBUG
	std::cout << "Destroy Object" << std::endl;
#endif
}
