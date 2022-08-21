#pragma once

#include <vector>
#include <memory>

namespace Renderer
{
	class AnimSprite;
}

class HealthComponent
{
public:
	HealthComponent(int health);

	void Hurt(int damageValue);
	void Heal(int healValue);

	int GetHealth() { return _health; }

	float GetInviolabilityTime() { return _inviolability_time; }

	void UpdateInviolability(float deltaTime);
private:
	int _health;
	int _max_health;

	float _inviolability_time = 0.f;
};