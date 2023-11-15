#pragma once

#include "UIElement.h"

namespace Renderer
{
    class Sprite;
}

class Image : public UIElement
{
public:
    /// @brief 
    /// @param position позиция 
    /// @param size размер
    /// @param sprite спрайт для картинки
    Image(const glm::vec2& position, const glm::vec2& size, Renderer::Sprite* sprite);
    Image(const glm::vec2& position, const glm::vec2& size);

    ~Image();

    void SetSprite(Renderer::Sprite* sprite);

    /// @brief Используется чтобы поменять не только свою позицию, но и зависимого элемента(-ов)
    /// @param position 
    virtual void ChangePosition(const glm::vec2& position) override;
private:
    Renderer::Sprite* _sprite;
};