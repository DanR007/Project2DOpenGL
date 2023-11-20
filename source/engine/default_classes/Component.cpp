#include "../../main.h"

#include "Component.h"

Component::~Component()
{
#ifdef DEBUG
	std::cout << "Destroy Component" << std::endl;
#endif
}
