#pragma once

#include "../default_classes/Component.h"

class UIElement : public Component
{
public:
	UIElement(const glm::vec2& position, const glm::vec2& size);
	virtual ~UIElement();

	virtual void SetRender(bool need_to_render) { _need_to_render = need_to_render; };
	bool GetNeedToRender() const { return _need_to_render; }

protected:
	bool _need_to_render = true;
};