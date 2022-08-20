#include "MainCharacter.h"

#include "enemies/MeleeEnemy.h"

#include "../engine/renderer/AnimSprite.h"
#include "../engine/renderer/ShaderRender.h"
#include "../engine/renderer/TextureRender.h"

#include "../engine/managers/PhysicsManager.h"
#include "../engine/managers/GameManager.h"

#include "../engine/physics/Collider.h"

#include "../main.h"

#include <iostream>

namespace Game
{
	MainCharacter::MainCharacter(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader,
		const std::string& initSubtextureName, const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation, const float startMoveSpeed)
		:Pawn(std::move(texture), std::move(shader), initSubtextureName, startPosition, startSize, startRotation, startMoveSpeed)
	{
		_collider = std::make_shared<Physics::Collider>(EObjectTypes::EOT_Character, startSize);

		_collider->SetCollisionResponse(EObjectTypes::EOT_Enemy, EResponseType::ERT_Overlap);
		_collider->SetCollisionResponse(EObjectTypes::EOT_Character, EResponseType::ERT_Overlap);
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
	}

	void MainCharacter::Move(float deltaTime)
	{
		if (!is_ignore_move_input && move_vector != glm::vec2(0.f, 0.f) &&
			PhysicsManager::CanMove(this, _position + move_vector * deltaTime * move_speed))
		{
			GameManager::MoveAllActors(move_vector * deltaTime * move_speed);
		}
	}

	void MainCharacter::ChangeMoveVector(const glm::vec2& inputVector)
	{
		move_vector += inputVector;
	}

	void MainCharacter::Input(GLFWwindow* currentWindow, int key, int scancode, int action, int mode)
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
}