#pragma once

#include "../Unit.h"

class Soldier : public Unit
{
public:
    Soldier(const glm::ivec2& position);

    ~Soldier();

    /// @brief возвращает время требуемое для тренировки солдата
    /// @return 
    float GetTrainingTime() const { return _trainig_time; }
private:
    float _trainig_time = 0.f;
};