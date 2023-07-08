#include "../../../engine/default_classes/Pawn.h"

#include "BuildingTypes.h"


class Building : public Pawn
{
public:
	Building(const glm::ivec2& pivot_position, const glm::ivec2& size, const EBuildingType& type);
	~Building();

	void Replace() { _replace = true; }
protected:
	Building(const std::string& initSubtextureName, const glm::vec2& startPosition = glm::vec2(0.f),
		const glm::vec2& startSize = glm::vec2(1.f), const float& rotation = 0.f);

	glm::ivec2 _building_size;

	EBuildingType _type;

	bool _replace = false;
};