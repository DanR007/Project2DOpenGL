#include "Building.h"


class Lumber : public Building
{
public:
	Lumber(const glm::ivec2& position);
	~Lumber();

	virtual void Replace() override;
};