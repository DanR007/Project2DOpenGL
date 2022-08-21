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

		virtual void Move(const float deltaTime) override;

		virtual void PointReached() override;

		virtual void ChangePatrolPointsCoordinate(const glm::vec2& value) override;

		virtual void SetPatrolPoints(const std::vector<glm::vec2>& patrolPoints) override;
	protected:

		std::vector<glm::vec2> patrol_points;

		glm::vec2 current_patrol_point;

		int patrol_direction = 1;
		size_t index = 0;

	private:
	};

}