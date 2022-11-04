#pragma once
#include "EPhysicsTypes.h"

#include <map>

#include <glm/vec2.hpp>
#include <memory>

#include "../Delegate.h"

#include "../default_classes/Component.h"



namespace Physics
{
	class Collider : public Component
	{
	public:
		Collider(const EObjectTypes objectType, const glm::vec2& position, const glm::vec2& size = glm::vec2(100.f, 100.f)) 
			: Component(nullptr)
		{
			_position = position; _size = size; _object_type = objectType;
		}

		void SetCollisionResponse(EObjectTypes objectType, EResponseType responseType);
		void SetPosition(const glm::vec2& newPosition) { _position = newPosition; }
		void SetSize(const glm::vec2& newSize) { _size = newSize; }

		EResponseType GetResponseType(EObjectTypes objectType) { return objects_response_map[objectType]; }
		EObjectTypes GetObjectType() { return _object_type; }
		glm::vec2 GetSize() { return _size; }
		glm::vec2 GetPosition() { return _position; }

		template<class T, class C>
		void AddOverlapDelegate(C* own_class, T method)
		{
			_delegate_overlap.Connect(own_class, method);
		}

		void Overlap(Game::Actor* actor) { _delegate_overlap(actor); }

	protected:
		glm::vec2 _size, _position;

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
