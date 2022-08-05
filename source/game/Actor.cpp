#include "Actor.h"

#include "../engine/renderer/AnimSprite.h"

#include "../engine/managers/ResourcesManager.h"

namespace Game
{
	Actor::Actor(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader, const std::string& initSpriteName,
		const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation)
	{
		sprite = new Renderer::Sprite(texture, shader, initSpriteName, 
			startPosition, startSize, startRotation);

		position = startPosition;
		rotation = startRotation;
		size = startSize;
	}

	Actor::~Actor()
	{
		delete sprite;
		sprite = nullptr;
	}

	void Actor::Draw() { sprite->Render(); }
}