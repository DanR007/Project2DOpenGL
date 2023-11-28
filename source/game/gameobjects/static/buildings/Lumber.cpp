#include "Lumber.h"

#include "../../units/Lumberjack.h"

#include "../../../../main.h"

#include "../../../../engine/managers/EngineManager.h"
#include "../../../../engine/managers/GameManager.h"

Lumber::Lumber(const glm::ivec2& position):
	Building(position, glm::ivec2(2), EBuildingType::EBT_Lumber)
{
	_cost.push_back(std::make_pair(EResourceTypes::ERT_Wood, 10));
	_cost.push_back(std::make_pair(EResourceTypes::ERT_Gold, 0));
	_cost.push_back(std::make_pair(EResourceTypes::ERT_Stone, 0));
}

Lumber::~Lumber()
{
}

void Lumber::Replace()
{
	Building::Replace();
	_worker = GetEngine()->GetWorld()->SpawnActor<Lumberjack>(_map_position);
	_worker->SetPlayerID(_player_id);
}
