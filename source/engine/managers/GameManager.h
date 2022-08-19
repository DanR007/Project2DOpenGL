#pragma once

#include <memory>

#include <glm/vec2.hpp>

#include "ResourcesManager.h"

#include "../../game/Pawn.h"

namespace Renderer
{
	class Texture2D;
	class ShaderProgram;
}

namespace Game
{
	class Actor;
	class Pawn;
}

class GameManager
{
public:
	template<typename T>
	static std::shared_ptr<T> SpawnActor(const std::string& initSpriteName, const glm::vec2& actorPosition = glm::vec2(0.f), const glm::vec2& actorSize = glm::vec2(100.f, 100.f), const float actorRotation = 0.f,
		std::shared_ptr<Renderer::Texture2D> texture = ResourcesManager::GetTexture("textureAtlas"),
		std::shared_ptr<Renderer::ShaderProgram> shader = ResourcesManager::GetShaderProgram("spriteShader"))
	{
		std::shared_ptr<T> newActor = std::make_shared<T>(texture, shader, initSpriteName, actorPosition, actorSize, actorRotation); all_actors.push_back(std::static_pointer_cast<Game::Actor>(newActor));
		return newActor;
	}

	static void MoveAllActors(const glm::vec2& valuePosition);

	static void Update(const float deltaTime);
private:
	static std::vector<std::shared_ptr<Game::Actor>> all_actors;

	friend class PhysicsManager;
};

