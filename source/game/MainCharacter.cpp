#include "MainCharacter.h"

#include "HealthComponent.h"

#include "weapons/WeaponComponent.h"

#include "enemies/MeleeEnemy.h"

#include "gameobjects/HealActor.h"

#include "../engine/renderer/AnimSprite.h"
#include "../engine/renderer/ShaderRender.h"
#include "../engine/renderer/TextureRender.h"

#include "../engine/managers/PhysicsManager.h"
#include "../engine/managers/GameManager.h"

#include "../engine/physics/Collider.h"

#include "../engine/controllers/PlayerController.h"

#include "../main.h"

#include <iostream>

namespace Game
{
	MainCharacter::MainCharacter(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader,
		const std::string& initSubtextureName, const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation, const float startMoveSpeed)
		:Pawn(texture, shader, initSubtextureName, startPosition, startSize, startRotation, startMoveSpeed)
	{
		_collider = std::make_shared<Physics::Collider>(EObjectTypes::EOT_Character, startPosition, startSize);

		_collider->SetCollisionResponse(EObjectTypes::EOT_Enemy, EResponseType::ERT_Overlap);
		_collider->SetCollisionResponse(EObjectTypes::EOT_Character, EResponseType::ERT_Ignore);
		_collider->SetCollisionResponse(EObjectTypes::EOT_Projectile, EResponseType::ERT_Ignore);
		_collider->SetCollisionResponse(EObjectTypes::EOT_InteractiveObject, EResponseType::ERT_Overlap);

		_health_component = std::make_shared<HealthComponent>(10);

		_weapon_component = std::make_shared<WeaponComponent>(std::move(texture), std::move(shader), "pistol", startPosition + (startSize / 2.f), startSize / 4.f, startRotation);

		//_player_controller = std::make_shared<PlayerController>(100.f);
		//_player_controller->SetCharacter(this);
	}

	MainCharacter::~MainCharacter()
	{

	}


	void MainCharacter::BeginPlay()
	{
		
	}

	void MainCharacter::Update(float deltaTime)
	{
		Move(deltaTime);
		Actor::Update(deltaTime);

		if (_health_component->GetInviolabilityTime() > 0.f)
		{
			_health_component->UpdateInviolability(deltaTime);
		}
		_health_component->RenderHealth();

		_weapon_component->Update(deltaTime);
	}

	void MainCharacter::Move(float deltaTime)
	{
		if (!is_ignore_move_input && move_vector != glm::vec2(0.f, 0.f) &&
			PhysicsManager::CanMove(this, _position + move_vector * deltaTime * move_speed))
		{
			GameManager::MoveAllActors(move_vector * deltaTime * move_speed);
			//_weapon_component->FollowOwner(move_vector * deltaTime * move_speed);
		}
	}

	void MainCharacter::ChangeMoveVector(const glm::vec2& inputVector)
	{
		move_vector += inputVector;
	}

	void MainCharacter::InputKeyboard(GLFWwindow* currentWindow, int key, int scancode, int action, int mode)
	{
		switch (action)
		{
		case GLFW_PRESS:
			switch (key)
			{
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(currentWindow, GLFW_TRUE);
				break;
			case GLFW_KEY_W:
				if (!is_ignore_move_input)
					ChangeMoveVector(up_vector);
				break;
			case GLFW_KEY_S:
				if (!is_ignore_move_input)
					ChangeMoveVector(up_vector * -1.f);
				break;
			case GLFW_KEY_D:
				if (!is_ignore_move_input)
					ChangeMoveVector(right_vector);
				break;
			case GLFW_KEY_A:
				if (!is_ignore_move_input)
					ChangeMoveVector(right_vector * -1.f);
				break;
			}
			break;
		case GLFW_RELEASE:
			switch (key)
			{
			case GLFW_KEY_W:
				ChangeMoveVector(up_vector * -1.f);
				break;
			case GLFW_KEY_S:
				ChangeMoveVector(up_vector);
				break;
			case GLFW_KEY_D:
				ChangeMoveVector(right_vector * -1.f);
				break;
			case GLFW_KEY_A:
				ChangeMoveVector(right_vector);
				break;
			}
			break;
		/*case GLFW_REPEAT:

			break;*/
		}
	}
	void MainCharacter::InputMouse(GLFWwindow* currentWindow, int button, int action, int mode)
	{
		switch (action)
		{
		case GLFW_PRESS:
			switch (button)
			{
			case GLFW_MOUSE_BUTTON_1:
			{
				double xPos, yPos;
				glfwGetCursorPos(currentWindow, &xPos, &yPos);
				_weapon_component->Shoot(glm::vec2(float(xPos), float(yPos)));
			}
			break;
			}
			break;
		case GLFW_RELEASE:
			switch (button)
			{
			case GLFW_MOUSE_BUTTON_1:
			{
				double xPos, yPos;
				glfwGetCursorPos(currentWindow, &xPos, &yPos);
				_weapon_component->Shoot(glm::vec2(float(xPos), float(yPos)));
			}
			break;
			}
			break;
		case GLFW_REPEAT:
			switch (button)
			{
			case GLFW_MOUSE_BUTTON_1:
			{
				double xPos, yPos;
				glfwGetCursorPos(currentWindow, &xPos, &yPos);
				_weapon_component->Shoot(glm::vec2(float(xPos), float(yPos)));
			}
			break;
			}
			break;
		}
	}
	void MainCharacter::Overlap(std::shared_ptr<Actor> overlappingActor)
	{
		std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(overlappingActor);
		std::shared_ptr<HealActor> heal = std::dynamic_pointer_cast<HealActor>(overlappingActor);
		if (_health_component->GetInviolabilityTime() <= 0.f)
		{
			if (enemy)
			{
				_health_component->Hurt(enemy->GetOverlapDamage());
				return;
			}
			else
			{
				std::shared_ptr<Enemy> bullet = std::dynamic_pointer_cast<Enemy>(overlappingActor);
				//here add a damage of bullet and make cast to a bullet class
			}
		}
		else
		{

		}

		if (heal)
		{
			_health_component->Heal(heal->GetHealValue());
			heal->DestroyActor();
		}

	}
}