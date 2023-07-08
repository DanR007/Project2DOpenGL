#include "AnimSprite.h"
#include "TextureRender.h"

#include "../../main.h"

namespace Renderer
{
	AnimSprite::AnimSprite(RenderImage* image, Actor* owner, const glm::vec2& position,
		const glm::vec2& size, const float rotation)
		:Sprite(image,
			owner,
			position,
			size,
			rotation)
	{
		current_anim_duration = states_map.end();
	}

	AnimSprite::~AnimSprite()
	{
#ifdef DEBUG
		std::cout << "Destroy AnimSprite" << std::endl;
#endif
	}
	

	void AnimSprite::InsertState(const std::string& state, std::vector<std::pair<std::string, float>> subTextureDuration)
	{
		states_map.emplace(state, subTextureDuration);
	}
	void AnimSprite::SetState(const std::string& state)
	{
		auto it = states_map.find(state);
		if (it == states_map.end())
		{
			std::cerr << "Cant find state: " + state << std::endl;
			return;
		}
		if (current_anim_duration != it)
		{
			current_anim_time = 0;
			current_frame = 0;
			current_anim_duration = it;
			is_dirty = true;

			SetNewSprite(current_anim_duration->second[current_frame].first);
		}
	}

	void AnimSprite::Update(const float deltaTime)
	{
		if (current_anim_duration != states_map.end())
		{
			current_anim_time += deltaTime;

			while (current_anim_time >= current_anim_duration->second[current_frame].second)
			{
				current_anim_time -= current_anim_duration->second[current_frame].second;
				current_frame++;

				if (current_frame == current_anim_duration->second.size())
				{
					current_frame = 0;
				}

				SetNewSprite(current_anim_duration->second[current_frame].first);
			}
		}
	}
}