#include "Soldier.h"

#include "../../../../main.h"

Soldier::Soldier(const glm::ivec2& position) : Unit(position)
{
#ifdef DEBUG
    std::cout << "Создал солдата\n";
#endif
}


Soldier::~Soldier()
{
    
}