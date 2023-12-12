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

    template<typename T>
    void StartTraining();
private:
    bool _is_training = false;
    float _max_training_time, _current_training_time;

    /// @brief Используется для создания всех кнопок, progress bar, казармы в виджете
    void ConfigureUI();

    /// @brief хранит все кнопки юнитов для казармы
    Widget* _wdg;
};
