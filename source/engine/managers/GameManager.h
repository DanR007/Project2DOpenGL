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

		
		
		if(std::dynamic_pointer_cast<Game::Actor>(newActor))
			std::dynamic_pointer_cast<Game::Actor>(newActor)->SetIterator(_all_actors.emplace(_all_actors.end(), newActor));

		return newActor;
	}

	static void MoveAllActors();

	static void Update(const float deltaTime);
	static void BeginPlay();

	static void SetGameOver(bool isGameOver) { _is_game_over = isGameOver; }
	static void SetIterator(std::vector<std::shared_ptr<Game::Actor>>::iterator it) { _it = it; }

	static void DeleteActor(Game::Actor* actor);
private:

	static std::vector<std::shared_ptr<Game::Actor>>::iterator _it;

	static std::vector<std::shared_ptr<Game::Actor>> _all_actors;

	static bool _is_game_over;
	friend class PhysicsManager;
	friend class Physics::Collider;
};

