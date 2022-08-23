#pragma once 
#include "../Actor.h"

namespace Game
{
	class HealActor :public Actor
	{
	public:
		HealActor(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader,
			const std::string& initSubtextureName,
			const glm::vec2& startPosition, const glm::vec2& startSize = glm::vec2(1.f), const float startRotation = 0.f);

		virtual void BeginPlay() override;

		int GetHealValue() { return _heal_value; }

		void SetHealValue(int newHealValue) { _heal_value = newHealValue; }
	private:
		int _heal_value;
	};
}