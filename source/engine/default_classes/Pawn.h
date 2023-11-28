#pragma once

#include "Actor.h"

#include "../../game/gameobjects/static/resources/ResourceTypes.h"

class Controller;

class Pawn : public Actor
{
public:
	Pawn(const std::string& initSubtextureName
		, const glm::vec2& startPosition/*lower left point*/
		, const glm::vec2& startSize = glm::vec2(1.f)
		, const uint8_t& render_layer = 0
		, const float startRotation = 0.f);

	Pawn() = delete;

	virtual void Update(const float& deltaTime) override;

	virtual ~Pawn();

	glm::ivec2 GetMapPosition() const { return _map_position; }
	Controller* GetController() { return _controller; }
	bool GetIsSelected() const { return _is_selected; }
	inline uint8_t GetID() const { return _player_id; }

	void SetSelected(bool is_selected);
	inline void SetMapPosition(const glm::ivec2& map_pos) { _map_position = map_pos; }
	inline void SetPlayerID(const uint8_t& id) { _player_id = id; }

	std::vector<std::pair<EResourceTypes, size_t>> GetCost() const;
protected:
	uint8_t _player_id;

	Controller* _controller = nullptr;

	bool _is_selected;

	int _hp;
	int _max_hp;
	
	glm::ivec2 _map_position;

	Renderer::Sprite* _selected_sprite = nullptr;

	std::vector<std::pair<EResourceTypes, size_t>> _cost;
private:

};
