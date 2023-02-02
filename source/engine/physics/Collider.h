#pragma once
#include "EPhysicsTypes.h"

#include <map>
#include <memory>

#include "../Delegate.h"

#include "../default_classes/Component.h"



namespace Physics
{
	class Collider : public MovableComponent
	{
	public:
		Collider(const EObjectTypes objectType, Game::Actor* owner, const glm::vec2& position, const glm::vec2& size = glm::vec2(100.f, 100.f), const float& rotation = 0.f) 
			: MovableComponent(owner, position, size, rotation)
		{
			_object_type = objectType;
		}

		void SetCollisionResponse(EObjectTypes objectType, EResponseType responseType);

		inline EResponseType GetResponseType(EObjectTypes objectType) { return objects_response_map[objectType]; }
		inline EObjectTypes GetObjectType() const { return _object_type; }

		template<class T, class C>
		void AddOverlapDelegate(C* own_class, T method)
		{
			_delegate_overlap.Connect(own_class, method);
		}

		void Overlap(Game::Actor* actor) { _delegate_overlap(actor); }

	protected:
		std::map<EObjectTypes, EResponseType> objects_response_map =
		{
			{EObjectTypes::EOT_Enemy, EResponseType::ERT_Block},
			{EObjectTypes::EOT_Character, EResponseType::ERT_Block},
			{EObjectTypes::EOT_StaticObject, EResponseType::ERT_Block},
			{EObjectTypes::EOT_Projectile, EResponseType::ERT_Overlap},
			{EObjectTypes::EOT_DynamicObject, EResponseType::ERT_Block},
			{EObjectTypes::EOT_InteractiveObject, EResponseType::ERT_Ignore}
		};

		EObjectTypes _object_type;
		Delegate _delegate_overlap;
	};
}
