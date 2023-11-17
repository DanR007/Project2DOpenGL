#pragma once

#include <iostream>

#include "UIElement.h"

#include "../Delegate.h"

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

    /// @brief на кнопку нажали
    void Click();

    /// @brief выставляем (если потребуется) событие клика на кнопку
    /// @tparam C класс, который будет использовать этот делегат
    /// @tparam M метод внутри переданного класса, который будет обрабатывать
    /// @param own_class 
    /// @param method 
    template<class C, class M>
	void SetOnClickEvent(C* own_class, M method)
	{
		if (own_class)
		{
			_on_click_event.Connect(own_class, method);
		}
		else
		{
			std::cerr << "Own class by function not valid" << std::endl;
		}
	}
private:
    /// @brief наполнение может быть как текстом, так и просто картинкой
    UIElement* _filling = nullptr;
    /// @brief фон для кнопки, чтобы она выделялась
    Renderer::Sprite* _background = nullptr;
    /// @brief коллайдер, считывающий нажатие на кнопку
    Physics::Collider* _collider = nullptr;
    /// @brief событие клика
    Delegate _on_click_event;
};