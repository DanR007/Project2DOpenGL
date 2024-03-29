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
	class Collider : public Component
	{
	public:

		Collider(const EObjectTypes objectType, Object* owner, const glm::vec2& position, const glm::vec2& size = glm::vec2(100.f, 100.f), const float& rotation = 0.f) 
			: Component(owner, position, size, rotation)
		{
			_object_type = objectType;
		}

		virtual ~Collider();

		void SetCollisionResponse(EObjectTypes objectType, EResponseType responseType);
		void ClearOverlappingActors() { _overlapping_actors.clear(); }

		inline EResponseType GetResponseType(EObjectTypes objectType) { return objects_response_map[objectType]; }
		inline EResponseType GetTraceResponseType(ERaycastTypes ray_type) { return ray_response_map[ray_type]; }
		inline EObjectTypes GetObjectType() const { return _object_type; }
		inline std::vector<Actor*> GetOverlappingActors() 
		{
			return _overlapping_actors;
		}

		template<class T, class C>
		void AddOverlapDelegate(C* own_class, T method)
		{
			_delegate_overlap.Connect(own_class, method);
		}

		void Overlap(Actor* actor);

	protected:
		std::map<EObjectTypes, EResponseType> objects_response_map =
		{
			{EObjectTypes::EOT_Pawn, EResponseType::ERT_Block},
			{EObjectTypes::EOT_Character, EResponseType::ERT_Block},
			{EObjectTypes::EOT_StaticObject, EResponseType::ERT_Block},
			{EObjectTypes::EOT_DynamicObject, EResponseType::ERT_Block},
			{EObjectTypes::EOT_UI, EResponseType::ERT_Ignore}
		};
		std::map<ERaycastTypes, EResponseType> ray_response_map =
		{
			{ERaycastTypes::ERT_Character, EResponseType::ERT_Block},
			{ERaycastTypes::ERT_StaticObject, EResponseType::ERT_Block},
			{ERaycastTypes::ERT_Visible, EResponseType::ERT_Block}
		};

		EObjectTypes _object_type;
		Delegate _delegate_overlap;

		std::vector<Actor*> _overlapping_actors;
	};
}
