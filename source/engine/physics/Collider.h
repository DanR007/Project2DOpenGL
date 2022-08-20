#pragma once
#include "EPhysicsTypes.h"

#include <map>

#include <glm/vec2.hpp>

namespace Physics
{
	class Collider
	{
	public:
		Collider(const EObjectTypes objectType, const glm::vec2& size = glm::vec2(100.f, 100.f)) { _size = size; _object_type = objectType; }
		void SetCollisionResponse(EObjectTypes objectType, EResponseType responseType);

		EResponseType GetResponseType(EObjectTypes objectType) { return objects_response_map[objectType]; }
		EObjectTypes GetObjectType() { return _object_type; }

		glm::vec2 GetSize() { return _size; }

		void SetSize(const glm::vec2& newSize) { _size = newSize; }
	private:
		glm::vec2 _size;

		std::map<EObjectTypes, EResponseType> objects_response_map =
		{
			{EObjectTypes::EOT_Enemy, EResponseType::ERT_Block},
			{EObjectTypes::EOT_Character, EResponseType::ERT_Block},
			{EObjectTypes::EOT_StaticObject, EResponseType::ERT_Block},
			{EObjectTypes::EOT_Projectile, EResponseType::ERT_Overlap}
		};

		EObjectTypes _object_type;
	};
}
