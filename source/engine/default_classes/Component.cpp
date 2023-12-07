#include "../../main.h"

#include "Component.h"

Component::~Component()
{
#ifdef DEBUG_DESTRUCTOR
	std::cout << "Destroy Component" << std::endl;
#endif
}
