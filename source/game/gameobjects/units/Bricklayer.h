#pragma once

#include "Worker.h"

/// @brief каменщик
class Bricklayer : public Worker
{
public:
	Bricklayer(const glm::ivec2& position);
	~Bricklayer();

protected:

};