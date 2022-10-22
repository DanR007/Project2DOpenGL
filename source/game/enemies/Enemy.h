#pragma once

#include "../../engine/default_classes/Pawn.h"

class EnemyController;

namespace Game
{
	class Enemy : public Pawn
	{
	public:
		using Pawn::Pawn;
		/*Enemy(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader, const std::string& initSubtextureName,
			const glm::vec2& startPosition = glm::vec2(0.f), const glm::vec2& startSize = glm::vec2(1.f), const float startRotation = 0.f,
			const float moveSpeed = 0.f);*/

		virtual void PointReached() {}

		virtual void ChangePatrolPointsCoordinate(const glm::vec2& value) {}

		virtual void SetPatrolPoints(const std::vector<glm::vec2>& patrolPoints) { patrol_points = patrolPoints; }

		int GetOverlapDamage() { return overlap_damage; }
		void Hurt(int damage);

		void FindPathToPlayer();

		EnemyController* GetEnemyController();
	protected:
		int _health;

		std::vector<glm::vec2> patrol_points;

		glm::vec2 current_patrol_point;

		int patrol_direction = 1;
		size_t index = 0;

		int overlap_damage = 1;
	private:
	};
}