#include "HealthComponent.h"

#include "../engine/managers/GameManager.h"

#include <cmath>
#include <iostream>

HealthComponent::HealthComponent(int health)
{
	_max_health = health;
	_health = health;
}

void HealthComponent::Hurt(int damageValue)
{
	_health = std::max(0, _health - damageValue);
	if (_health == 0)
	{
		GameManager::SetGameOver(true);
	}
	else
	{
		_inviolability_time = 1.f;
	}
	std::cout << _health << std::endl;
}

void HealthComponent::Heal(int healValue)
{
	_health = std::min(_max_health, _health + healValue);
}

void HealthComponent::UpdateInviolability(float deltaTime)
{
	_inviolability_time = std::max(0.f, _inviolability_time - deltaTime);
}
