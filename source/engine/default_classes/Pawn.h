#pragma once

#include "Actor.h"

class Controller;

class Pawn : public Actor
{
public:
	Pawn(const std::string& initSubtextureName,
		const glm::vec2& startPosition = glm::vec2(0.f), const glm::vec2& startSize = glm::vec2(1.f), const float startRotation = 0.f);
	Pawn(Pawn&& p) noexcept;

	Pawn() = delete;

	void Update(const float& deltaTime) override;

	~Pawn();

	Controller* GetController() { return _controller; }
protected:

	Controller* _controller = nullptr;
private:

};
