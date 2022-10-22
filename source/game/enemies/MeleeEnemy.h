#pragma once

#include "Enemy.h"


namespace Game
{
	class MainCharacter;

	class MeleeEnemy : public Enemy
	{
	public:
		MeleeEnemy(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader, const std::string& initSubtextureName,
			const glm::vec2& startPosition = glm::vec2(0.f), const glm::vec2& startSize = glm::vec2(1.f), const float startRotation = 0.f,
			const float moveSpeed = 0.f);

		
	protected:

		

	private:


	};

}