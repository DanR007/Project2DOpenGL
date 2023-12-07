#pragma once

#include "Building.h"

class Widget;

class Barracks : public Building
{
public:
    Barracks(const glm::ivec2& position);
    virtual ~Barracks();

    virtual void Replace() override;

    virtual void SetSelected(bool is_selected) override;
private:
    /// @brief Используется для создания всех кнопок казармы в виджете
    void ConfigureButtons();

    /// @brief хранит все кнопки юнитов для казармы
    Widget* _wdg;
};
