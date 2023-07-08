#include "Lumber.h"


Lumber::Lumber(const glm::ivec2& position):
	Building(position, glm::ivec2(2), EBuildingType::EBT_Lumber)
{
	_hp = 100;
}

Lumber::~Lumber()
{
}
