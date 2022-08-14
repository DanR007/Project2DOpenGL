#pragma once


#include "Sprite.h"


#include <map>
namespace Renderer
{
	class AnimSprite : public Sprite
	{
	public:
		AnimSprite(std::shared_ptr<Texture2D> texture, std::shared_ptr <ShaderProgram> shader,
			const std::string& initialSubtextureName, const glm::vec2& position = glm::vec2(0.f),
			const glm::vec2& size = glm::vec2(1.f), const float rotation = 0.f);

		~AnimSprite();

		virtual void Render() const override;


		void InsertState(const std::string& state, std::vector<std::pair<std::string, float>> subTextureDuration);
		void SetState(const std::string& state);
		void Update(const float deltaTime);

		
	private:
		std::map<std::string, std::vector<std::pair<std::string, float>>> states_map;

		size_t current_frame = 0;
		float current_anim_time = 0;

		std::map<std::string, std::vector<std::pair<std::string, float>>>::const_iterator current_anim_duration;
		mutable bool is_dirty = false;
	};

}