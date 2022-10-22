#pragma once 

#include "../../engine/default_classes/Actor.h"


namespace Game
{
	namespace Objects
	{
		class Wall : public Actor
		{
		public:
			Wall(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader,
				const std::string& initSubtextureName,
				const glm::vec2& startPosition, const glm::vec2& startSize = glm::vec2(1.f), const float startRotation = 0.f);
		};
	}
}