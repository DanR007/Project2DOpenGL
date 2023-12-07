#pragma once

#include "Building.h"

/// @brief Лесопилка
class Lumber : public Building
{
public:
	Lumber(const glm::ivec2& position);
	~Lumber();

	virtual void Replace() override;
};