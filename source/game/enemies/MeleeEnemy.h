#pragma once

#include "../Pawn.h"

namespace Game
{
	class MainCharacter;

	class MeleeEnemy : public Pawn
	{
	public:
		MeleeEnemy(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader, const std::string& initSubtextureName,
			const std::vector<glm::vec2>& patrolPoints, const glm::vec2& startPosition = glm::vec2(0.f), const glm::vec2& startSize = glm::vec2(1.f), const float startRotation = 0.f,
			const float moveSpeed = 0.f);

		virtual void Move(const float deltaTime) override;

		virtual void PointReached();

		void ChangePatrolPointsCoordinate(const glm::vec2& value);
	protected:

		std::vector<glm::vec2> patrol_points;

		glm::vec2 current_patrol_point;

		int patrol_direction = 1;
		size_t index = 0;

	private:
	};

}