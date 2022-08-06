#include "Actor.h"

#include "../engine/renderer/AnimSprite.h"

#include "../engine/managers/ResourcesManager.h"

namespace Game
{
	Actor::Actor(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader, const std::string& subtextureName,
		const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation)
	{
		anim_sprite = new Renderer::AnimSprite(texture, shader, subtextureName,
			startPosition, startSize, startRotation);

		position = startPosition;
		rotation = startRotation;
		size = startSize;
	}

	Actor::~Actor()
	{
		delete anim_sprite;
		anim_sprite = nullptr;
	}

	void Actor::Draw() { anim_sprite->Render(); }

	void Actor::Update(float deltaTime)
	{
		anim_sprite->Update(deltaTime);
		anim_sprite->Render();
	}

	Renderer::AnimSprite* Actor::GetAnimSprite()
	{
		return anim_sprite;
	}
}