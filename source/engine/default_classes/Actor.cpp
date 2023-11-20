#include "Actor.h"

#include "../managers/EngineManager.h"
#include "../managers/RenderManager.h"

#include "../../main.h"

Actor::Actor(const std::string& initSubtextureName,
	const glm::vec2& startPosition, const glm::vec2& startSize, const uint8_t& render_layer, const float startRotation):
	Object(startPosition, startSize, startRotation)
{
	if (!initSubtextureName.empty())
	{
		_anim_sprite = GetEngine()->GetRenderManager()->CreateSprite<Renderer::AnimSprite>(this, 
		startPosition, startSize, initSubtextureName, "textureAtlas", render_layer, startRotation);
		Attach(_anim_sprite);
	}
	else
	{
		Destroy();
	}
}

Actor::~Actor()
{
#ifdef DEBUG
	std::cout << "Destroy Actor" << std::endl;
#endif
}


void Actor::Update(const float& deltaTime)
{
	
}

void Actor::BeginPlay()
{
}

	
void Actor::AddAnimState(const std::string& stateName, std::vector<std::pair<std::string, float>> subTextureDuration)
{
	_anim_sprite->InsertState(stateName, subTextureDuration);
}
void Actor::PlayAnim(const std::string& stateName)
{
	_anim_sprite->SetState(stateName);
}

