#pragma once

#include "Building.h"

/// @brief Каменоломня
class Quarry : public Building
{
public:
    /// @brief Конструктор каменоломни
    /// @param position позиция на карте
    Quarry(const glm::ivec2& position);

    ~Quarry();

    virtual void Replace() override;
};