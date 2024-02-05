#pragma once

#include "Building.h"

class Widget;
class Unit;

class Barracks : public Building
{
public:
    Barracks(const glm::ivec2& position);
    virtual ~Barracks();

    virtual void Replace() override;

    virtual void SetSelected(bool is_selected) override;

    /// @brief начинаем тренировку боевой единицы
    /// @tparam T класс военной единицы
    template<typename T>
    void StartTraining();

    /// @brief заканчиваем тренировку военной единицы и переносим на пустое место
    void EndTrainig();

    void TrainMelee();
    void TrainRange();
    void TrainStrongMelee();

private:
    bool _is_training = false;
    float _max_training_time, _current_training_time;

    /// @brief Используется для создания всех кнопок, progress bar, казармы в виджете
    void ConfigureUI();

    /// @brief хранит все кнопки юнитов для казармы
    Widget* _wdg;

    Unit* _new_unit;

    
};
