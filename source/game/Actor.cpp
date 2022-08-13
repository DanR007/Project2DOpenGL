#include "Actor.h"

#include "../engine/renderer/AnimSprite.h"

#include "../engine/managers/ResourcesManager.h"

namespace Game
{
	Actor::Actor(std::shared_ptr<Renderer::AnimSprite> animSprite,
		const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation)
	{
		anim_sprite = animSprite;

		anim_sprite->SetPosition(startPosition);
		anim_sprite->SetSize(startSize);
		anim_sprite->SetRotation(startRotation);

		position = startPosition;
		rotation = startRotation;
		size = startSize;
	}

	Actor::~Actor()
	{

	}


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
		anim_sprite->SetPosition(newPosition);
	}
	void Actor::SetSize(const glm::vec2& newSize)
	{
		size = newSize;
		anim_sprite->SetSize(newSize);
	}
	void Actor::SetRotation(const float newRotation)
	{
		rotation = newRotation;
		anim_sprite->SetRotation(newRotation);
	}
}