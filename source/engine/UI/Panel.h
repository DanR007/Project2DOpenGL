#pragma	once

#include "UIElement.h"

namespace Renderer
{
	class Sprite;
}

class Panel : public UIElement
{
public:
	Panel(const glm::vec2& position, const glm::vec2& size, Renderer::Sprite* sprite);
	Panel(const glm::vec2& position, const glm::vec2& size);
	~Panel();

	Renderer::Sprite* GetSprite() { return _sprite; }

protected:
	Renderer::Sprite* _sprite = nullptr;
};