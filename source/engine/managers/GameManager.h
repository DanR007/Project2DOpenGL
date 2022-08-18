#pragma once

#include <memory>

#include <glm/vec2.hpp>

#include "ResourcesManager.h"

//#include "../../main.h"

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

static class GameManager
{
public:
	template<typename T>
	static std::shared_ptr<T> SpawnActor(const std::string& initSpriteName, const glm::vec2& actorPosition = glm::vec2(0.f), const glm::vec2& actorSize = glm::vec2(100.f, 100.f), const float actorRotation = 0.f,
		std::shared_ptr<Renderer::Texture2D> texture = ResourcesManager::GetTexture("textureAtlas"),
		std::shared_ptr<Renderer::ShaderProgram> shader = ResourcesManager::GetShaderProgram("spriteShader"))
	{
		return std::make_shared<T>(texture, shader, initSpriteName, actorPosition, actorSize, actorRotation);
	}

private:
	//std::vector<std::shared_ptr<Game::Actor>> all_actors;

};

