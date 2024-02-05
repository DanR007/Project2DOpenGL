#include "RangeSoldier.h"

#include "../../../../main.h"

RangeSoldier::RangeSoldier(const glm::ivec2& position) : Soldier(position)
{
#ifdef DEBUG
    std::cout << "Создал солдата дальнего боя\n";
#endif
}


RangeSoldier::~RangeSoldier()
{
    
}