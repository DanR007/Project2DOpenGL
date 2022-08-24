#pragma once

#include <vector>
#include <memory>

#include <glm/vec2.hpp>

namespace Renderer
{
	class Sprite;
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
	void UpdateHearts();

	void RenderHealth();
private:
	int _health;
	int _max_health;

	float _inviolability_time = 0.f;

	const glm::vec2 _c_heart_size = glm::vec2(32.f, 32.f);
	const glm::vec2 _c_heart_offset = glm::vec2(40.f, 0.f);

	std::vector<std::shared_ptr<Renderer::Sprite>> vector_of_health;
};