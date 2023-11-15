#include "Image.h"

#include "../renderer/Sprite.h"


Image::Image(const glm::vec2& position, const glm::vec2& size, Renderer::Sprite* sprite) :
    UIElement(position, size)
{
    _sprite = sprite;
}

Image::Image(const glm::vec2& position, const glm::vec2& size) :
    UIElement(position, size)
{
    _sprite = nullptr;
}

Image::~Image()
{
    if(_sprite)
    {
        _sprite->Destroy();
    }
}

void Image::SetSprite(Renderer::Sprite *sprite)
{
    _sprite = sprite;
}

void Image::ChangePosition(const glm::vec2 &position)
{
    SetPosition(position);
    _sprite->SetPosition(position);
}
