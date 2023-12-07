#pragma once
#include "UIElement.h"

#include <string>

namespace Renderer
{
	class Sprite;
}

class Text : public UIElement
{
public:
	Text(const glm::vec2& position, const glm::vec2& symbol_size = glm::vec2(20.f));
	virtual ~Text();
	
	void Clear();

	inline void SetText(const std::string& text_string)
	{
		_text_string = text_string;
		UpdateText();
	}

	inline std::string GetText() const { return _text_string; }
	
	virtual void SetRender(bool need_to_render) override;
protected:
	void ToLower();
	void UpdateText();

	std::vector<Renderer::Sprite*> _symbol_sprites;

	std::string _text_string;

	glm::vec2 _symbol_size;
};