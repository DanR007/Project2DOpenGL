#pragma once
#include "../../engine/default_classes/Component.h"
#include "EWeaponTypes.h"

#include <memory>
#include <string>

#include <glm/vec2.hpp>

namespace Renderer
{
	class Texture2D;
	class ShaderProgram;
	class Sprite;
}

class WeaponComponent : public Component
{
public:
	WeaponComponent(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader, const std::string& initSpriteName, Game::Actor* owner,
		const glm::vec2& position, const glm::vec2& size, const float rotation);
	void Shoot(const glm::vec2 mousePosition);

	void UpdateReloadTime(float deltaTime);

	void Update(float deltaTime);

	inline float GetReloadTime() const { return _reload_time; }

	void FollowOwner(const glm::vec2 value);
	bool SetWeaponActive(bool isActive) { _weapon_active = isActive; }
protected:


private:
	float _reload_time = 0.f;

	int _damage_current_weapon = weapon_type_and_damage[_weapon_type].first;

	bool _weapon_active = false;

	EWeaponTypes _weapon_type = EWeaponTypes::EWT_Pistol;
	std::shared_ptr<Renderer::Sprite> _sprite_weapon;
};