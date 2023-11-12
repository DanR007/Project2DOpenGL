#include "Bricklayer.h"

Bricklayer::Bricklayer(const glm::ivec2& position):
	Worker(position, EResourceTypes::ERT_Stone)
{
}

Bricklayer::~Bricklayer()
{
}