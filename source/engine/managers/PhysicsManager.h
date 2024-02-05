#pragma once

#include <memory>
#include <vector>

#include <glm/vec2.hpp>

#include "../physics/EPhysicsTypes.h"
#include "../physics/RaycastResult.h"

class Object;
class Actor;

class GameManager;
class PhysicsTests;

class Unit;

class Button;

namespace Physics 
{
	class Collider;

	class PhysicsManager
	{
	public:
		PhysicsManager(GameManager* world) : _world(world) {}

		bool CanMove(Actor* checkActor, const glm::vec2& delta);
		void CheckOverlapping(Physics::Collider* first_collider);

		/// @brief используется в основном для создания пресонажей на карте
		/// @param type 
		/// @param owner 
		/// @param position в целочисленных координатах (позиции на карте)
		/// @param size 
		/// @return 
		Collider* CreateCollider(const EObjectTypes& type, Object* owner, const glm::ivec2 position, const glm::vec2& size);
		/// @brief используется для назначения позиций коллайдеров для кнопок и прочих объектов не из карты
		/// @param type 
		/// @param owner 
		/// @param window_position 
		/// @param size 
		/// @return 
		Collider* CreateCollider(const EObjectTypes& type, Object* owner, const glm::vec2 window_position, const glm::vec2& size);

		void Update();

		bool Raycast(RaycastResult& result, const glm::vec2& start, const glm::vec2& end, const ERaycastTypes& raycast_type,
			Actor* self = nullptr, bool ignore_self = true);

		Unit* GetUnitUnderCursor(const glm::vec2& cursor_pos);
		void CheckClickButton(const glm::vec2& cursor_pos);

		void Erase(Collider* collider);
	private:
		void Multithreading(int start, int end);
		/// @brief проверка AABB типа для пересечения коллайдеров
		/// @param pos_first_collider позиция
		/// @param size_first_collider размер первого коллайдера
		/// @param pos_second_collider позиция
		/// @param size_second_collider размер второго коллайдера
		/// @return пересекаются ли коллайдеры
		bool IsIntersection(const glm::vec2& pos_first_collider, const glm::vec2& size_first_collider, const glm::vec2& pos_second_collider, const glm::vec2& size_second_collider);
		/// @brief перекрывают ли два коллайдера
		/// @param first_collider первый коллайдер
		/// @param second_collider второй коллайдер
		/// @return 
		bool IsOverlap(Physics::Collider* first_collider, Physics::Collider* second_collider);
		/// @brief блокируется ли первый коллайдер вторым и наоборот
		/// @param delta_pos смещение первого коллайдера
		/// @param first_collider первый коллайдер
		/// @param second_collider второй коллайдер
		/// @return 
		bool IsBlocking(const glm::vec2& delta_pos, Physics::Collider* first_collider, Physics::Collider* second_collider);
		/// @brief проверка находится ли курсор в районе UI 
		/// @param cursor_pos позиция курсора
		/// @return 
		bool InUI(const glm::vec2& cursor_pos);

		GameManager* _world;
		std::vector<Collider*> _all_colliders;

		friend class PhysicsTests;
	};
}