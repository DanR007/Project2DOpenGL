#include <map>

#include "../../../engine/default_classes/Pawn.h"

#include "BuildingTypes.h"

class Worker;

class Building : public Pawn
{
public:
	Building(const glm::ivec2& pivot_position, const glm::ivec2& size, const EBuildingType& type);
	~Building();

	virtual void Replace();

	bool GetIsReplaced() const { return _replace; }
	glm::ivec2 GetBuildingSize() const { return _building_size;	}

	bool CanReplace();

	virtual void Update(const float& deltaTime) override;
protected:
	Building(const std::string& initSubtextureName
		, const glm::vec2& startPosition/*lower left point*/
		, const glm::vec2& startSize = glm::vec2(1.f)
		, const uint8_t& render_layer = 0
		, const float startRotation = 0.f);

	Worker* _worker = nullptr;

	glm::ivec2 _building_size;

	EBuildingType _type;

	bool _replace = false;
};