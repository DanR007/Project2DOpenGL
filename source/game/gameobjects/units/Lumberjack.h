#include "Worker.h"

#include "../"
class Lumberjack : public Worker
{
public:
	Lumberjack(const glm::ivec2& position);
	~Lumberjack();

	virtual void Update(const float& deltaTime) override;

protected:
	Wood*
};