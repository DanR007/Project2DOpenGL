#include "../Unit.h"

#include "../Resource.h"


class Worker : public Unit
{
public:
	Worker(const glm::ivec2& position, const EResourceTypes& type);
	virtual ~Worker();

	virtual void Update(const float& deltaTime) override;

	void Work(const float& deltaTime);

	void Returning();
protected:
	uint8_t _resource_count = 0;
	uint8_t _max_resource_count = 10;

	bool _returning = false;

	float _work_time = 0.f;
	float _work_time_need_to_earn = 1.f;

	Resource* _resource;

	Cell* _home_cell;

	EResourceTypes _collectable_type;
};