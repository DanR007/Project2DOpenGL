#include "Lumber.h"

#include "../units/Lumberjack.h"

#include "../../../main.h"

#include "../../../engine/managers/EngineManager.h"
#include "../../../engine/managers/GameManager.h"

Lumber::Lumber(const glm::ivec2& position):
	Building(position, glm::ivec2(2), EBuildingType::EBT_Lumber)
{
	_hp = 100;
}

Lumber::~Lumber()
{
}

void Lumber::Replace()
{
	Building::Replace();
	_worker = GetEngine()->GetWorld()->SpawnActor<Lumberjack>(_map_position);
}
