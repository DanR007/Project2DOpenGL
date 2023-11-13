#include "Quarry.h"

#include "../../units/Bricklayer.h"

#include "../../../../main.h"

#include "../../../../engine/managers/EngineManager.h"
#include "../../../../engine/managers/GameManager.h"

Quarry::Quarry(const glm::ivec2& position):
	Building(position, glm::ivec2(2), EBuildingType::EBT_Quarry)
{
	_hp = 100;

	_cost.push_back(std::make_pair(EResourceTypes::ERT_Wood, 20));
	_cost.push_back(std::make_pair(EResourceTypes::ERT_Gold, 0));
	_cost.push_back(std::make_pair(EResourceTypes::ERT_Stone, 0));
}

Quarry::~Quarry()
{
}

void Quarry::Replace()
{
	Building::Replace();
	_worker = GetEngine()->GetWorld()->SpawnActor<Bricklayer>(_map_position);
	_worker->SetPlayerID(_player_id);
}