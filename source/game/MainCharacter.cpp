#include "MainCharacter.h"

#include "enemies/MeleeEnemy.h"

#include "../engine/renderer/AnimSprite.h"
#include "../engine/renderer/ShaderRender.h"
#include "../engine/renderer/TextureRender.h"

#include "../engine/managers/PhysicsManager.h"

#include "../main.h"

#include <iostream>

namespace Game
{
	MainCharacter::MainCharacter(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader,
		const std::string& initSubtextureName, const float startMoveSpeed, const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation)
		:Pawn(std::move(texture), std::move(shader), initSubtextureName, startMoveSpeed, startPosition, startSize, startRotation)
	{

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
			PhysicsManager::CanMove(std::move(all_actors), position + move_vector * deltaTime * move_speed, size))
		{
			for (std::shared_ptr<Game::Actor> actor : all_actors)
			{
				actor->SetPosition(actor->GetPosition() - move_vector * deltaTime * move_speed);
			}

			for (std::shared_ptr<Game::Pawn> pawn : all_pawns)
			{
				pawn->SetPosition(pawn->GetPosition() + move_vector * -1.f);

				std::dynamic_pointer_cast<MeleeEnemy>(pawn)->ChangePatrolPointsCoordinate(move_vector * -1.f);
				//std::static_pointer_cast<MeleeEnemy>(pawn)->ChangePatrolPointsCoordinate(move_vector * -1.f);
			}
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