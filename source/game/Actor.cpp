#include "Actor.h"

#include "../engine/renderer/AnimSprite.h"

#include "../engine/managers/ResourcesManager.h"

namespace Game
{
	Actor::Actor(std::shared_ptr<Renderer::AnimSprite> animSprite,
		const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation)
	{
		anim_sprite = animSprite;

		position = startPosition;
		rotation = startRotation;
		size = startSize;
	}

	Actor::~Actor()
	{

	}

	void Actor::Draw() { anim_sprite->Render(); }

	void Actor::Update(float deltaTime)
	{
		anim_sprite->Update(deltaTime);
		anim_sprite->Render();
	}

	std::shared_ptr<Renderer::AnimSprite> Actor::GetAnimSprite()
	{
		return anim_sprite;
	}
}