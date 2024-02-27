#pragma once

#include "Soldier.h"

class RangeSoldier : public Soldier
{
public:
    RangeSoldier(const glm::ivec2& position);

    ~RangeSoldier();


    virtual void Update(const float& deltaTime) override;

    
private:
    int _range = 5;
};