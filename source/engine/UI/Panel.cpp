#include "Panel.h"

#include "../../main.h"

#include "../managers/EngineManager.h"
#include "../managers/RenderManager.h"

Panel::Panel(const glm::vec2& position, const glm::vec2& size, Renderer::Sprite* sprite) :
	UIElement(position, size), _sprite(sprite)
{
}

Panel::Panel(const glm::vec2& position, const glm::vec2& size):
	UIElement(position, size)
{
	_sprite = GetEngine()->GetRenderManager()->CreateSprite<Renderer::Sprite>(nullptr, position, size, "background", "textureAtlas", 1);
}

Panel::~Panel()
{
	if (_sprite)
	{
		_sprite->Destroy();
		_sprite = nullptr;
	}
}
