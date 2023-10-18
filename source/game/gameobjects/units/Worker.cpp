#include "Worker.h"

#include "../../../main.h"

#include "../../../engine/managers/EngineManager.h"
#include "../../../engine/managers/GameManager.h"

#include "../../../engine/AI/NavMesh.h"
#include "../../../engine/controllers/Controller.h"
#include "../../../engine/controllers/PlayerController.h"

Worker::Worker(const glm::ivec2& position, const EResourceTypes& type):
	Unit(position)
{
	_collectable_type = type;
	_resource = GetEngine()->GetWorld()->GetNavMesh()->GetNearestResource(position, _collectable_type);

	_home_cell = GetEngine()->GetWorld()->GetMap()[position.y][position.x];

	if (_resource)
	{
		#ifdef DEBUG
std::cout << "Find position is: " 
<< _resource->GetCell()->_position.x
<< " " 
<< _resource->GetCell()->_position.y
<< " "
<< _resource->GetCell()->_symbol
<< std::endl;
				#endif
		MoveTo(_resource->GetCell());
	}
}

Worker::~Worker()
{
}

void Worker::Update(const float& deltaTime)
{
	Work(deltaTime);
	Unit::Update(deltaTime);
}

void Worker::Work(const float& deltaTime)
{
	if (_controller && _controller->GetPathComplete())
	{
		if (_returning)
		{
#ifdef DEBUG
			std::cout << "Worker is brought 10 resources" << std::endl;
#endif
			GetEngine()->GetWorld()->GetPlayerController(_player_id)->AddResource(_collectable_type, _resource_count);

			_returning = false;
			_resource_count = 0;

			if (_resource && !_resource->IsEmpty())
			{
				MoveTo(_resource->GetCell());
			}
			else
			{
				FindNewResource();
			}
		}
		else
		{
			_work_time += deltaTime;
			if (_work_time >= _work_time_need_to_earn)
			{
				_work_time = 0.f;
				_resource_count += _resource->EarnResources();

#ifdef DEBUG
				std::cout << "Earn one resource" << std::endl;
#endif
				if (_resource->IsEmpty())
				{
					_resource = nullptr;
				}

				if (_resource_count < _max_resource_count)
				{
					if (!_resource)
					{
						FindNewResource();
					}
				}
				else
				{
					Returning();
				}

				
			}
		}
	}
}

void Worker::FindNewResource()
{
#ifdef DEBUG
	std::cout << "Finding new resource " << std::endl;
#endif
	_resource = GetEngine()->GetWorld()->GetNavMesh()->GetNearestResource(_map_position, _collectable_type);
						#ifdef DEBUG
std::cout << "Find position is: " 
<< _resource->GetCell()->_position.x
<< " " 
<< _resource->GetCell()->_position.y
<< " "
<< _resource->GetCell()->_symbol
<< std::endl;
				#endif
	if(_resource)
		MoveTo(_resource->GetCell());
}


void Worker::Returning()
{
#ifdef DEBUG
	std::cout << "Returning to home" << std::endl;
#endif
	_returning = true;
	MoveTo(_home_cell);
}
