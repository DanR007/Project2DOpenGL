#include "Pawn.h"

#include "../../main.h"

#include "../managers/PhysicsManager.h"
#include "../managers/GameManager.h"
#include "../managers/RenderManager.h"

#include "../renderer/AnimSprite.h"
#include "../renderer/ShaderRender.h"
#include "../renderer/TextureRender.h"

#include "../controllers/Controller.h"


	Pawn::Pawn(const std::string& initSubtextureName,
		const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation):
		Actor(initSubtextureName, startPosition, startSize, startRotation)
	{
		_selected_sprite = GetEngine()->GetRenderManager()->CreateSprite<Renderer::Sprite>(this, startPosition, startSize, "selected");
		_components.push_back(_selected_sprite);

		_map_position = GetWorld()->ConvertToMapSpace(startPosition);

		_is_selected = false;

		_hp = 1;
	}

	Pawn::Pawn(Pawn&& p) noexcept
		:Actor(std::move(p))
	{
		if(_controller)
			delete _controller;

		_controller = p._controller;
		_is_selected = p._is_selected;
		_map_position = p._map_position;
		_hp = p._hp;
	}

	void Pawn::Update(const float& deltaTime)
	{
		if(_controller)
			_controller->Move(deltaTime);
		Actor::Update(deltaTime);
	}

	Pawn::~Pawn()
	{
#ifdef DEBUG
		std::cout << "Destroy Pawn" << std::endl;
#endif
		if (_controller)
		{
			delete _controller;
			_controller = nullptr;
		}
	}
