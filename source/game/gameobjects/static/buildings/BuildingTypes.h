#pragma once

#include <map>
#include <string>

/// @brief типы зданий
enum class EBuildingType
{
	EBT_Lumber,
	EBT_Quarry,
	EBT_None
};
/// @brief словарь который хранит имена строений и их тип
extern std::map<EBuildingType, std::string> _building_sprite_name;

