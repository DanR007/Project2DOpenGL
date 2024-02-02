#include "RangeSoldier.h"

#include "../../../../main.h"

RangeSoldier::RangeSoldier(const glm::ivec2& position) : Unit(position)
{
#ifdef DEBUG
    std::cout << "Создал солдата дальнего боя\n";
#endif
}


RangeSoldier::~RangeSoldier()
{
    
}