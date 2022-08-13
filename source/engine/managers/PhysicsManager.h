#pragma once

#include <memory>
#include <vector>

#include <glm/vec2.hpp>

namespace Game
{ 
	class Actor;
}

static class PhysicsManager
{
public:
	static bool CanMove(std::vector<std::shared_ptr<Game::Actor>>& actorNeedToCheck, const glm::vec2& nextPosition, const glm::vec2& sizeActor);

};