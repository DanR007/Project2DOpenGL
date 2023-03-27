#pragma once

#include "../../engine/default_classes/Pawn.h"

struct Cell;

class Unit : public Game::Pawn
{
public:
	Unit(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader, const std::string& initSubtextureName,
		const glm::vec2& startPosition = glm::vec2(0.f), const glm::vec2& startSize = glm::vec2(1.f), const float& rotation = 0.f);

	Unit(Unit&& u) noexcept;

	void SetChoicing(bool is_choicing) { _is_choicing = is_choicing; }

	void MoveTo(const Cell& cell);
private:
	bool _is_choicing;

	int _hp;

};