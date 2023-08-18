#pragma once

#include "Actor.h"

#include "../../game/ResourceTypes.h"

class Controller;

class Pawn : public Actor
{
public:
	Pawn(const std::string& initSubtextureName,
		const glm::vec2& startPosition = glm::vec2(0.f), const glm::vec2& startSize = glm::vec2(1.f), const float startRotation = 0.f);
	Pawn(Pawn&& p) noexcept;

	Pawn() = delete;

	virtual void Update(const float& deltaTime) override;

	virtual ~Pawn();

	glm::ivec2 GetMapPosition() const { return _map_position; }
	Controller* GetController() { return _controller; }
	bool GetIsSelected() const { return _is_selected; }
	inline uint8_t GetID() const { return _player_id; }

	inline void SetSelected(bool is_selected) { _is_selected = is_selected; }
	inline void SetMapPosition(const glm::ivec2& map_pos) { _map_position = map_pos; }
	inline void SetPlayerID(const uint8_t& id) { _player_id = id; }

	std::vector<std::pair<EResourceTypes, size_t>> GetCost() const;
protected:
	uint8_t _player_id;

	Controller* _controller = nullptr;

	bool _is_selected;

	int _hp;

	glm::ivec2 _map_position;

	Renderer::Sprite* _selected_sprite = nullptr;

	std::vector<std::pair<EResourceTypes, size_t>> _cost;
private:

};
