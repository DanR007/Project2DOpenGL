#pragma once

#include "Bullet.h"

namespace Game
{
	class PistolBullet : public Bullet
	{
	public:
		PistolBullet(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader,
			const std::string& initSubtextureName,
			const glm::vec2& startPosition, const glm::vec2& startSize = glm::vec2(1.f), const float startRotation = 0.f);
		~PistolBullet() = default;

		void Overlap(Actor* overlappingActor);
		//virtual void DestroyActor() override;
	protected:
	};
}