#include "Actor.h"

#include "../renderer/AnimSprite.h"
#include "../renderer/TextureRender.h"
#include "../renderer/ShaderRender.h"

#include "../managers/ResourcesManager.h"
#include "../managers/GameManager.h"
#include "../managers/PhysicsManager.h"

#include "../physics/Collider.h"

namespace Game
{
	Actor::Actor(const std::string& initSubtextureName,
		const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation)
	{
		_anim_sprite = std::make_unique<Renderer::AnimSprite>(std::move(ResourcesManager::GetTexture("textureAtlas")), std::move(ResourcesManager::GetShaderProgram("spriteShader")),
			initSubtextureName, this, startPosition, startSize, startRotation);

		_world_position = startPosition;
		_rotation = startRotation;
		_size = startSize;
		
	}

	Actor::Actor(Actor&& a) noexcept
	{
		_relative_position = a._relative_position;
		_world_position = a._world_position;
		_rotation = a._rotation;
		_size = a._size;

		_collider = a._collider;
		_iterator = a._iterator;
		_anim_sprite = std::move(a._anim_sprite);
	}

	Actor::~Actor()
	{
		
	}


	void Actor::Update(float deltaTime)
	{
		_anim_sprite->Update(deltaTime);
	}

	void Actor::BeginPlay()
	{
	}

	std::shared_ptr<Renderer::AnimSprite> Actor::GetAnimSprite() { return std::move(_anim_sprite); }

	void Actor::SetPosition(const glm::vec2& new_position)
	{
		_world_position = new_position;
		_anim_sprite->SetPosition(new_position);
		_collider->SetPosition(new_position);
	}
	void Actor::SetSize(const glm::vec2& new_size)
	{
		_size = new_size;
		_anim_sprite->SetSize(new_size);
		_collider->SetSize(new_size);
	}
	void Actor::SetRotation(const float& new_rotation)
	{
		_rotation = new_rotation;
		_anim_sprite->SetRotation(new_rotation);
		_collider->SetRotation(new_rotation);
	}
	void Actor::SetRelativePosition(const glm::vec2& new_position)
	{
		glm::vec2 d_pos = new_position - _relative_position;

		_relative_position = new_position;
		_anim_sprite->AddWorldPosition(d_pos);
		_collider->AddWorldPosition(d_pos);
	}
	void Actor::AddWorldPosition(const glm::vec2& d_pos)
	{
		_world_position += d_pos;
		_anim_sprite->AddWorldPosition(d_pos);
		_collider->AddWorldPosition(d_pos);
	}
	void Actor::AddWorldRotation(const float& d_rot)
	{
		_rotation += d_rot;
		_anim_sprite->AddWorldRotation(d_rot);
		_collider->AddWorldRotation(d_rot);
	}
	void Actor::AddAnimState(const std::string& stateName, std::vector<std::pair<std::string, float>> subTextureDuration)
	{
		_anim_sprite->InsertState(stateName, subTextureDuration);
	}
	void Actor::PlayAnim(const std::string& stateName)
	{
		_anim_sprite->SetState(stateName);
	}
	void Actor::DestroyActor()
	{
		GetWorld()->DeleteActor(_iterator);
	}
}