#include "AnimSprite.h"
#include "TextureRender.h"
#include <iostream>

namespace Renderer
{
	AnimSprite::AnimSprite(std::shared_ptr<Texture2D> texture, std::shared_ptr<ShaderProgram> shader,
		const std::string& initialSubtextureName, Game::Actor* owner, const glm::vec2& position,
		const glm::vec2& size, const float rotation)
		:Sprite(texture,
			shader,
			initialSubtextureName,
			owner,
			position,
			size,
			rotation)
	{
		current_anim_duration = states_map.end();
	}

	AnimSprite::~AnimSprite()
	{

	}
	

	void AnimSprite::Render() const
	{
		if (is_dirty)
		{
			auto subTexture = _texture->GetSubTexture(current_anim_duration->second[current_frame].first);

			const GLfloat textureCoords[] =
			{
				subTexture.left_bottom_UV.x, subTexture.left_bottom_UV.y,
				subTexture.left_bottom_UV.x, subTexture.right_upper_UV.y,
				subTexture.right_upper_UV.x, subTexture.left_bottom_UV.y,
				subTexture.right_upper_UV.x, subTexture.right_upper_UV.y
			};


			glBindBuffer(GL_ARRAY_BUFFER, texture_coord_buffer);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(textureCoords), &textureCoords);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			is_dirty = false;
		}
		Sprite::Render();
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
				is_dirty = true;

				if (current_frame == current_anim_duration->second.size())
				{
					current_frame = 0;
				}
			}
		}

		Render();
	}
}