#include "HealthComponent.h"

#include "../engine/managers/GameManager.h"
#include "../engine/managers/ResourcesManager.h"

#include "../engine/renderer/Sprite.h"

#include <cmath>
#include <iostream>



HealthComponent::HealthComponent(int health)
{
	_max_health = health;
	_health = health - 2;

	for (int i = 0; i < _max_health; i++)
	{
		std::shared_ptr heart = std::make_shared<Renderer::Sprite>(ResourcesManager::GetTexture("textureAtlas"), ResourcesManager::GetShaderProgram("spriteShader"), "fullHeart", 
			_c_heart_offset * float(i) + glm::vec2(10.f, window_size.y - 50.f), _c_heart_size);


		vector_of_health.push_back(heart);

		if (_health >= i)
			heart->SetNewSprite("fullHeart");
		else
			heart->SetNewSprite("emptyHeart");
	}
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

	UpdateHearts();

	std::cout << _health << std::endl;
}

void HealthComponent::Heal(int healValue)
{
	_health = std::min(_max_health, _health + healValue);

	UpdateHearts();
}

void HealthComponent::UpdateInviolability(float deltaTime)
{
	_inviolability_time = std::max(0.f, _inviolability_time - deltaTime);
}

void HealthComponent::UpdateHearts()
{
	for (int i = 0; i < _max_health; i++)
	{
		if (_health >= i)
			vector_of_health[i]->SetNewSprite("fullHeart");
		else
			vector_of_health[i]->SetNewSprite("emptyHeart");
	}
}

void HealthComponent::RenderHealth()
{
	for (int i = 0; i < _max_health; i++)
	{
		vector_of_health[i]->Render();
	}
}
