#pragma once
#include "../../engine/default_classes/Actor.h"

class Unit;

class Goal : public Game::Actor
{
public:
	Goal(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader,
		const std::string& initSubtextureName,
		const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation);

	virtual void Update(float deltaTime) override;

	void SetUnit(Unit* unit) { _unit = unit; }
private:
	Unit* _unit = nullptr;


};