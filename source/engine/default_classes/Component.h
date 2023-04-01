#pragma once

#include <glm/vec2.hpp>


namespace Game
{
	class Actor;
}

class Component
{
public:
	Component(Game::Actor* owner = nullptr)
	{
		_owner = owner;
	}
	~Component() { _owner = nullptr; }

	inline Game::Actor* GetOwner() const { return _owner; }

	virtual void Attach(Game::Actor* owner) { _owner = owner; }

protected:
	Game::Actor* _owner;
};

class MovableComponent:public Component
{
public:
	MovableComponent(Game::Actor* owner = nullptr,
		const glm::vec2& position = glm::vec2(0.f),
		const glm::vec2& size = glm::vec2(1.f),
		const float& rotation = 0.f) : Component(owner)
	{
		_world_position = position;
		_size = size;
		_world_rotation = rotation;

		Rotate();
	}
	~MovableComponent() { _owner = nullptr; }

	void Attach(Game::Actor* owner) override;

	void SetPosition(const glm::vec2& new_position)
	{
		_world_position = new_position;
	}
	void SetSize(const glm::vec2& new_size)
	{
		_size = new_size;
	}
	void SetRotation(const float new_rotation)
	{
		_world_rotation = new_rotation;
		Rotate();
	}

	inline glm::vec2 GetPosition() const { return _world_position; }
	inline glm::vec2 GetSize() const { return _size; }
	inline float GetRotation() const { return _world_rotation; }
	inline glm::vec2 GetXAxis() const { return _x_axis; }
	inline glm::vec2 GetYAxis() const { return _y_axis; }

	void AddWorldRotation(const float& d_rot) { _world_rotation += d_rot; Rotate(); }
	void AddWorldPosition(const glm::vec2& d_pos) { _world_position += d_pos; }
protected:
	glm::vec2 _x_axis = glm::vec2(1.f, 0.f), _y_axis = glm::vec2(0.f, 1.f);

	glm::vec2 _world_position, _size;
	float _world_rotation;

private:
	void Rotate();
};