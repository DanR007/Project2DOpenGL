#pragma once

#include <memory>
#include <vector>

#include <glm/vec2.hpp>

namespace Game
{ 
	class Actor;
}

class PhysicsManager
{
public:
	static bool CanMove(const glm::vec2& nextPosition, const glm::vec2& sizeActor);

};