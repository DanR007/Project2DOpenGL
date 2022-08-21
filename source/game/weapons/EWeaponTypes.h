#pragma once

#include <map>



enum class EWeaponTypes
{
	EWT_Pistol,
	EWT_AssaultRifle,
	EWT_SniperRifle,
	EWT_SubMachineGun
};

//first element of pair is a damage and second is a time between shooting
extern std::map<EWeaponTypes, std::pair<uint8_t, float>> weapon_type_and_damage;
