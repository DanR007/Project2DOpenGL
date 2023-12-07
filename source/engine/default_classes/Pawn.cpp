#include "Pawn.h"

#include "../../main.h"

#include "../managers/PhysicsManager.h"
#include "../managers/GameManager.h"
#include "../managers/RenderManager.h"

#include "../renderer/AnimSprite.h"
#include "../renderer/ShaderRender.h"
#include "../renderer/TextureRender.h"

#include "../controllers/Controller.h"
#include "../controllers/PlayerController.h"

#include "../UI/Widget.h"
#include "../UI/ProgressBar.h"

#include "../physics/Collider.h"

	Pawn::Pawn(const std::string& initSubtextureName
		, const glm::vec2& startPosition
		, const glm::vec2& startSize
		, const uint8_t& render_layer
		, const float startRotation) : 
		Actor(initSubtextureName, startPosition, startSize, render_layer, startRotation)
	{
		_collider = GetEngine()->GetPhysicsManager()->CreateCollider(EObjectTypes::EOT_Pawn, this, startPosition, startSize);
		Attach(_collider);
		
		_selected_sprite = GetEngine()->GetRenderManager()->CreateSprite<Renderer::Sprite>(nullptr, startPosition, startSize, "selected", "textureAtlas", DYNAMIC);
		_selected_sprite->SetNeedToRender(_is_selected);
		Attach(_selected_sprite);

		_is_selected = false;

		_hp = 5;
		_max_hp = 10;
	}

	void Pawn::Update(const float& deltaTime)
	{
		if(_controller)
		{
			_controller->Move(deltaTime);
		}
		if(_selected_sprite)
		{
			_selected_sprite->SetNeedToRender(GetIsSelected());
		}
		Actor::Update(deltaTime);
	}

	Pawn::~Pawn()
	{
#ifdef DEBUG_DESTRUCTOR
		std::cout << "Destroy Pawn" << std::endl;
#endif
		if (_controller)
		{
			delete _controller;
			_controller = nullptr;
		}
	}

	std::vector<std::pair<EResourceTypes, size_t>> Pawn::GetCost() const
	{
		if (_cost.empty())
		{
			std::cout << "Cost is empty\n";
		}
		return _cost;
	}

void Pawn::SetSelected(bool is_selected)
{
	_is_selected = is_selected;

	float perc_hp = float(_hp) / _max_hp;

	ProgressBar* progress_bar = GetEngine()->GetWorld()->GetPlayerController(_player_id)->GetWidget()->FindElementByClass<ProgressBar>();
	if(progress_bar)
	{
		progress_bar->SetPercentage(perc_hp);
		progress_bar->SetRender(_is_selected);
	}
	else
	{
#ifdef DEBUG
		std::cout << "progress bar is null" << std::endl;
#endif // DEBUG
	}
}
