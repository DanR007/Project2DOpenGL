#include "Actor.h"

#include "../engine/renderer/AnimSprite.h"
#include "../engine/renderer/TextureRender.h"
#include "../engine/renderer/ShaderRender.h"

#include "../engine/managers/ResourcesManager.h"
#include "../engine/managers/GameManager.h"

namespace Game
{
	Actor::Actor(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader,
		const std::string& initSubtextureName,
		const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation)
	{
		anim_sprite = std::make_unique<Renderer::AnimSprite>(std::move(texture), std::move(shader), initSubtextureName, startPosition, startSize, startRotation);

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
		return std::move(anim_sprite);
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
	void Actor::AddAnimState(const std::string& stateName, std::vector<std::pair<std::string, float>> subTextureDuration)
	{
		anim_sprite->InsertState(stateName, subTextureDuration);
	}
	void Actor::PlayAnim(const std::string& stateName)
	{
		anim_sprite->SetState(stateName);
	}
}