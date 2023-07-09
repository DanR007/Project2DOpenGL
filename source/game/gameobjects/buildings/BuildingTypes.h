#include <map>
#include <string>

enum class EBuildingType
{
	EBT_Lumber,
	EBT_Quary,
	EBT_None
};

extern std::map<EBuildingType, std::string> _building_sprite_name;

