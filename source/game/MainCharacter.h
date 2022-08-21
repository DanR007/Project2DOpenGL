#pragma once

#include "Pawn.h"

#include "../main.h"

class WeaponComponent;

namespace Game
{
	class MainCharacter: public Pawn
	{
	public:
		MainCharacter(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader,
			const std::string& initSubtextureName, const glm::vec2& startPosition = glm::vec2(0.f), 
			const glm::vec2& startSize = glm::vec2(100.f, 100.f), const float startRotation = 0.f,
			const float startMoveSpeed = 0.f);

		~MainCharacter();
		virtual void BeginPlay();
		virtual void Move(const float deltaTime) override;
		virtual void Update(float deltaTime) override;
		virtual void ChangeMoveVector(const glm::vec2& value) override;

		void SetIgnoreMoveInput(bool isIgnore) { is_ignore_move_input = isIgnore; }

		bool GetIsIgnoreMoveInput() { return is_ignore_move_input; }

		void InputKeyboard(GLFWwindow* currentWindow, int key, int scancode, int action, int mode);
		void InputMouse(GLFWwindow* currentWindow, int button, int action, int mode);

		virtual void Overlap(std::shared_ptr<Actor> overlappingActor) override;
		virtual void DestroyActor() override { delete this; }
	protected:

		bool is_pause = false;
		bool is_ignore_move_input = false;

		std::shared_ptr<HealthComponent> _health_component;
		std::shared_ptr<WeaponComponent> _weapon_component;
	};
}