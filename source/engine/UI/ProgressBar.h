#pragma once

#include "UIElement.h"

#include <string>

namespace Renderer
{
    class Sprite;
}

/// @brief Элемент интерфейса, который отвечает за шкалу прогресса
class ProgressBar : public UIElement
{
public:
    /// @brief 
    /// @param position позиция шкалы
    /// @param size размер шкалы (незаполненного спрайта)
    ProgressBar(const glm::vec2& position, const glm::vec2& size);

    ~ProgressBar();

    /// @brief выставляем заполненность от 0 до 1 и меняем размер заполненного спрайта
    /// @param percentage 
    void SetPercentage(const float& percentage);
    /// @brief заполненная шкала прогресса
    /// @param full новый спрайт
    void SetFullSprite(Renderer::Sprite* full);
    /// @brief незаполненная шкала прогресса
    /// @param empty новый спрайт
    void SetEmptySprite(Renderer::Sprite* empty);
    /// @brief создаем спрайт заполненной шкалы прогресса по имени
    /// @param full_name название нового спрайта
    void SetFullSpriteByName(const std::string& full_name);
    /// @brief создаем спрайт пустой шкалы прогресса по имени
    /// @param empty_name название нового спрайта
    void SetEmptySpriteByName(const std::string& empty_name);

    /// @brief получение заполненности
    /// @return 
    float GetPercentage() const { return _percentage; }
    Renderer::Sprite* GetFullSprite() { return _full_sprite; }
    Renderer::Sprite* GetEmptySprite() { return _empty_sprite; }

    /// @brief Будем ли мы отображать шкалу прогресса
    /// @param need_to_render булевая переменная отображения
    virtual void SetRender(bool need_to_render) override;
private:
    /// @brief заполненность шкалы от 0 до 1
    float _percentage = 0.f;
    /// @brief спрайт заполненной шкалы
    Renderer::Sprite* _full_sprite = nullptr;
    /// @brief спрайт пустой шкалы
    Renderer::Sprite* _empty_sprite = nullptr;
};