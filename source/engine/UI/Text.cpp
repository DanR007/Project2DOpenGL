#include "Text.h"

#include "../managers/EngineManager.h"
#include "../managers/RenderManager.h"

Text::Text(const glm::vec2& position, const glm::vec2& symbol_size) :
	UIElement(position, symbol_size)
{
	_text_string = "";
	_symbol_size = symbol_size;

	UpdateText();
}

Text::~Text()
{
	Clear();
}

void Text::ToLower()
{
	for (int i = 0; i < _text_string.size(); i++)
	{
		if (_text_string[i] <= 'Z' && _text_string[i] >= 'A')
		{
			_text_string[i] = _text_string[i] - ('Z' - 'z');
		}
	}
}

void Text::UpdateText()
{
	Clear();
	ToLower();

	for (int i = 0; i < _text_string.size(); i++)
	{
		glm::vec2 position = _world_position + glm::vec2(_symbol_size.x * float(i), 0.f) + glm::vec2(float(i) * 2.f, 0.f);
		Renderer::Sprite* spr = GetEngine()->GetRenderManager()->CreateSprite<Renderer::Sprite>(nullptr, position, _symbol_size, _text_string.substr(i, 1), "textureAtlas");
		_symbol_sprites.push_back(spr);
	}

	SetSize(glm::vec2(_symbol_size.x * _text_string.size() + _text_string.size() * 2.f, _symbol_size.y));
}

void Text::Clear()
{
	for (Renderer::Sprite* spr : _symbol_sprites)
	{
		if (!spr->GetNeedToDestroy())
			spr->Destroy();
	}

	_symbol_sprites.clear();
}
