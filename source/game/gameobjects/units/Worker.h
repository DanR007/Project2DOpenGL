#include "../Unit.h"

#include "../Resource.h"


class Worker : public Unit
{
public:
	Worker(const glm::ivec2& position);
	~Worker();


protected:
	Resource* _resource;


};