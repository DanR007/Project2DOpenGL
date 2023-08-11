#include "Lumberjack.h"


Lumberjack::Lumberjack(const glm::ivec2& position):
	Worker(position, EResourceTypes::ERT_Wood)
{
}

Lumberjack::~Lumberjack()
{
}
