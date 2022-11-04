#include "WeaponComponent.h"
#include "PistolBullet.h"

#include "../../engine/managers/GameManager.h"

#include "../../engine/renderer/Sprite.h"

#include <cmath>
#include <iostream>

std::map<EWeaponTypes, std::pair<uint8_t, float>> weapon_type_and_damage = {
	{EWeaponTypes::EWT_Pistol, std::make_pair(5, 1.f)},
	{EWeaponTypes::EWT_AssaultRifle, std::make_pair(3, 0.5f)},
	{EWeaponTypes::EWT_SniperRifle, std::make_pair(10, 2.f)},
	{EWeaponTypes::EWT_SubMachineGun, std::make_pair(2, 0.5f)}
};

WeaponComponent::WeaponComponent(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader, 
	const std::string& initSpriteName, const glm::vec2& position, const glm::vec2& size, const float rotation)
{
	_sprite_weapon = std::make_shared<Renderer::Sprite>(texture, shader, initSpriteName, position, size, rotation);
}

void WeaponComponent::Shoot(const glm::vec2& mousePosition)
{
	std::cout << "Shoot" << std::endl;
	if (_reload_time <= 0.f)
	{
		switch (_weapon_type)
		{
		case EWeaponTypes::EWT_Pistol:
		{
			std::shared_ptr<Game::PistolBullet> newBullet = GetWorld()->SpawnActor<Game::PistolBullet>("pistolBullet", _sprite_weapon->GetPosition(), _sprite_weapon->GetSize(), _sprite_weapon->GetRotation());

			newBullet->SetDamage(5);
			newBullet->SetSpeed(200.f);

			double length = std::sqrt(std::pow(mousePosition.x - _sprite_weapon->GetPosition().x, 2) + std::pow(mousePosition.y - _sprite_weapon->GetPosition().y, 2));

			newBullet->SetMoveVector(glm::vec2((mousePosition - _sprite_weapon->GetPosition()).x / length,
				(mousePosition - _sprite_weapon->GetPosition()).y / length * -1.f));


			_reload_time = weapon_type_and_damage[EWeaponTypes::EWT_Pistol].second;
		}
			break;
		}
	}
}

void WeaponComponent::UpdateReloadTime(float deltaTime)
{
	_reload_time = std::max(0.f, _reload_time - deltaTime);
}

void WeaponComponent::Update(float deltaTime)
{
	if (_reload_time > 0.f)
		UpdateReloadTime(deltaTime);

	_sprite_weapon->Render();
}

void WeaponComponent::FollowOwner(const glm::vec2 value)
{
	_sprite_weapon->SetPosition(_sprite_weapon->GetPosition() + value);
}
