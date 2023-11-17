#pragma once

#include "Object.h"

#include <string>
#include <vector>
#include <memory>

#include <glm/vec2.hpp>

namespace Renderer
{
	class Sprite;
	class AnimSprite;
	class Texture2D;
	class ShaderProgram;
}
namespace Physics
{
	class Collider;
}

class Component;

class Actor : public Object
{
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="initSubtextureName">Subtexture name of animation sprite</param>
	/// <param name="startPosition">Position of actor. </param>
	/// <param name="startSize">Size of actor, collider, sprite</param>
	/// <param name="render_layer">ZERO for static and ONE for dynamic </param>
	/// <param name="startRotation">Rotation of actor, collider, sprite</param>
	Actor(const std::string& initSubtextureName
		, const glm::vec2& startPosition/*lower left point*/
		, const glm::vec2& startSize = glm::vec2(1.f)
		, const uint8_t& render_layer = 0
		, const float startRotation = 0.f
		);

	Actor() = delete;
	virtual ~Actor();

	virtual void Update(const float& deltaTime);
	virtual void BeginPlay();

	/// @brief Получение спрайта с анимациями
	/// @return 
	inline Renderer::AnimSprite* GetAnimSprite() { return _anim_sprite; } 
	inline Physics::Collider* GetCollider() const { return _collider; }

	void SetCollider(Physics::Collider* collider) { _collider = collider; }

	/// @brief добавление анимаций
	/// @param stateName название анимации
	/// @param subTextureDuration анимация с длительностью на каждый кадр
	void AddAnimState(const std::string& stateName, std::vector<std::pair<std::string, float>> subTextureDuration);
	/// @brief проигрывание ранее добавленной анимации
	/// @param stateName название анимации
	void PlayAnim(const std::string& stateName);
protected:

	Physics::Collider* _collider = nullptr;
private:

	/// @brief спрайт хранящий все анимации
	Renderer::AnimSprite* _anim_sprite = nullptr;
};
