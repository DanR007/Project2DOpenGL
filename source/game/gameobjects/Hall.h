#pragma once

#include "WallActor.h"

#include <vector>

namespace Game
{
	namespace Objects
	{
		class Wall;

		class Hall
		{
		public:
			Hall(const glm::vec2& pointStart, const glm::vec2& pointEnd);

		private:
			std::vector<std::shared_ptr<Wall>> _wall_vector;
		};
	}
}