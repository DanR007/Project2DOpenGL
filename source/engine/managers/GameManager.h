#pragma once

#include <memory>

#include <glm/vec2.hpp>

#include "ResourcesManager.h"

#include "../../game/AllObjects.h"

#include "../../game/MainCharacter.h"

namespace Renderer
{
	class Texture2D;
	class ShaderProgram;
}

class GameManager
{
public:
	template<typename T>
	static std::shared_ptr<T> SpawnActor(const std::string& initSpriteName, const glm::vec2& actorPosition = glm::vec2(0.f), const glm::vec2& actorSize = glm::vec2(100.f, 100.f), const float actorRotation = 0.f,
		std::shared_ptr<Renderer::Texture2D> texture = ResourcesManager::GetTexture("textureAtlas"),
		std::shared_ptr<Renderer::ShaderProgram> shader = ResourcesManager::GetShaderProgram("spriteShader"))
	{
		std::shared_ptr<T> newActor = std::make_shared<T>(texture, shader, initSpriteName, actorPosition, actorSize, actorRotation); 

		if (/*typeid(*newActor) == typeid(Game::MainCharacter&)*/std::dynamic_pointer_cast<Game::MainCharacter>(newActor))
		{
			return newActor;
		}

		/*if (std::reinterpret_pointer_cast<Game::Pawn>(newActor))
		{
			all_pawns.push_back(newActor);
		}*/

		if(std::dynamic_pointer_cast<Game::Actor>(newActor))
			all_actors.push_back(newActor);

		return newActor;
	}

	static void MoveAllActors(const glm::vec2& valuePosition);

	static void Update(const float deltaTime);
	static void BeginPlay();

	static void SetGameOver(bool isGameOver) { _is_game_over = isGameOver; }
private:

	static bool _is_game_over;
	friend class PhysicsManager;
};

