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

	void Actor::SetPosition(const glm::vec2& newPosition)
	{
		position = newPosition;
		if (anim_sprite)
			anim_sprite->SetPosition(newPosition);
	}
	void Actor::SetSize(const glm::vec2& newSize)
	{
		size = newSize;
		if (anim_sprite)
			anim_sprite->SetSize(newSize);
	}
	void Actor::SetRotation(const float newRotation)
	{
		rotation = newRotation;
		if (anim_sprite)
			anim_sprite->SetRotation(newRotation);
	}
}