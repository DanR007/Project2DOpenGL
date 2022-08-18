#pragma once

#include <map>

//first element of pair is a damage and second is a time between shooting
static std::map<EWeaponTypes, std::pair<uint8_t, float>> weapon_type_and_damage = {
	{EWeaponTypes::EWT_Pistol, std::make_pair(5, 1.f)},
	{EWeaponTypes::EWT_AssaultRifle, std::make_pair(3, 0.5f)},
	{EWeaponTypes::EWT_SniperRifle, std::make_pair(10, 2.f)},
	{EWeaponTypes::EWT_SubMachineGun, std::make_pair(2, 0.5f)}
};

enum class EWeaponTypes
{
	EWT_Pistol,
	EWT_AssaultRifle,
	EWT_SniperRifle,
	EWT_SubMachineGun
};
