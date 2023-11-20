#include "Button.h"
#include "Image.h"
#include "Text.h"

#include "../renderer/Sprite.h"

#include "../physics/Collider.h"

Button::Button(const glm::vec2 &position, const glm::vec2 &size, Renderer::Sprite* background, UIElement *filling)
: UIElement(position, size)
{
    _background = background;
    _filling = filling;

    Attach(_background);
    Attach(_filling);

    glm::vec2 offset = glm::vec2(20);
    //размер кнопки должен быть больше чем наполнение
    SetSize(glm::vec2(_filling->GetSize()) + offset);
    //сдвигаем на половину размера относительно увеличенного размера
    _filling->AddWorldPosition(offset / 2.f);
}

Button::Button(const glm::vec2 &position, const glm::vec2 &size) : UIElement(position, size)
{

}

Button::~Button()
{

}

void Button::SetFilling(UIElement *filling)
{
    if(_filling)
    {
        _filling->Destroy();
    }

    _filling = filling;

    glm::vec2 offset = glm::vec2(20);
    //размер кнопки должен быть больше чем наполнение
    SetSize(glm::vec2(_filling->GetSize()) + offset);
    //сдвигаем на половину размера относительно увеличенного размера
    _filling->SetPosition(GetPosition() + offset /2.f);
    
}

void Button::SetCollider(Physics::Collider *collider)
{
    if(_collider)
    {
        _collider->Destroy();
    }

    _collider = collider;

    _collider->SetPosition(GetPosition());
    _collider->SetSize(GetSize());

    Attach(_collider);
}

void Button::SetBackground(Renderer::Sprite *background)
{
    if(_background)
    {
        _background->Destroy();
    }

    _background = background;

    _background->SetPosition(GetPosition());
    _background->SetSize(GetSize());

    Attach(_background);
}

void Button::Click()
{
#ifdef DEBUG
    std::cout << "Click event" << std::endl;
#endif
    _on_click_event();
}
