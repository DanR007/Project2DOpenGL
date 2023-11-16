#pragma once

#include "UIElement.h"

namespace Physics
{
    class Collider;
}
namespace Renderer
{
    class Sprite;
}

class Button : public UIElement
{
public:
    /// @brief 
    /// @param position позиция кнопки
    /// @param size размер
    /// @param background фон для кнопки
    /// @param filling наполнение кнопки (текст или картинка)
    Button(const glm::vec2& position, const glm::vec2& size, Renderer::Sprite* background, UIElement* filling);
    Button(const glm::vec2& position, const glm::vec2& size);
    
    ~Button();

    /// @brief Выставление наполнения
    /// @param filling 
    void SetFilling(UIElement* filling);
    /// @brief выставляем коллайдер
    /// @param collider 
    void SetCollider(Physics::Collider* collider);
    /// @brief выставляем задний фон
    /// @param background 
    void SetBackground(Renderer::Sprite* background);

    /// @brief Используется чтобы поменять не только свою позицию, но и зависимого элемента(-ов)
    /// @param position 
    virtual void ChangePosition(const glm::vec2& position) override;
private:
    /// @brief наполнение может быть как текстом, так и просто картинкой
    UIElement* _filling = nullptr;
    /// @brief фон для кнопки, чтобы она выделялась
    Renderer::Sprite* _background = nullptr;
    /// @brief коллайдер, считывающий нажатие на кнопку
    Physics::Collider* _collider = nullptr;
};