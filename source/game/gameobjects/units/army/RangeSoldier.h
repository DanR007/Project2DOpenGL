#pragma once

#include "../Unit.h"

class RangeSoldier : public Unit
{
public:
    RangeSoldier(const glm::ivec2& position);

    ~RangeSoldier();
};