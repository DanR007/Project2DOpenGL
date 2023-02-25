#pragma once
#include "EPhysicsTypes.h"

#include <map>
#include <memory>
#include <vector>
#include <mutex>

#include "../Delegate.h"

#include "../default_classes/Component.h"

#include "../managers/PhysicsManager.h"

namespace Physics
{
	class Collider : public MovableComponent
	{
	public:
		/// <summary>
		/// Spawn collider which have relative position (-size / 2)
		/// </summary>
		/// <param name="objectType"></param>
		/// <param name="owner"></param>
		/// <param name="position"></param>
		/// <param name="size"></param>
		/// <param name="rotation"></param>
		Collider(const EObjectTypes objectType, Game::Actor* owner, const glm::vec2& position, const glm::vec2& size = glm::vec2(100.f, 100.f), const float& rotation = 0.f) 
			: MovableComponent(owner, position, size, rotation)
		{
			_object_type = objectType;


			_relative_position = -size / 2.f;
		}

		void SetCollisionResponse(EObjectTypes objectType, EResponseType responseType);
		void ClearOverlappingActors() { _overlapping_actors.clear(); }

		inline EResponseType GetResponseType(EObjectTypes objectType) { return objects_response_map[objectType]; }
		inline EResponseType GetTraceResponseType(ERaycastTypes ray_type) { return ray_response_map[ray_type]; }
		inline EObjectTypes GetObjectType() const { return _object_type; }
		inline std::vector<Game::Actor*> GetOverlappingActors() 
		{
			std::lock_guard<std::mutex> lock(_mtx);
			return _overlapping_actors;
		}

		template<class T, class C>
		void AddOverlapDelegate(C* own_class, T method)
		{
			_delegate_overlap.Connect(own_class, method);
		}

		void Overlap(Game::Actor* actor);

	protected:
		std::map<EObjectTypes, EResponseType> objects_response_map =
		{
			{EObjectTypes::EOT_Pawn, EResponseType::ERT_Block},
			{EObjectTypes::EOT_Character, EResponseType::ERT_Block},
			{EObjectTypes::EOT_StaticObject, EResponseType::ERT_Block},
			{EObjectTypes::EOT_Projectile, EResponseType::ERT_Overlap},
			{EObjectTypes::EOT_DynamicObject, EResponseType::ERT_Block},
			{EObjectTypes::EOT_InteractiveObject, EResponseType::ERT_Ignore}
		};
		std::map<ERaycastTypes, EResponseType> ray_response_map =
		{
			{ERaycastTypes::ERT_Character, EResponseType::ERT_Block},
			{ERaycastTypes::ERT_StaticObject, EResponseType::ERT_Block},
			{ERaycastTypes::ERT_Visible, EResponseType::ERT_Block}
		};

		EObjectTypes _object_type;
		Delegate _delegate_overlap;

		std::vector<Game::Actor*> _overlapping_actors;

		std::mutex _mtx;

		friend void PhysicsManager::CheckOverlapping(std::shared_ptr<Physics::Collider> first_collider);
	};
}
