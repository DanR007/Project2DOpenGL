#pragma once

namespace Game
{
	class Actor;
}

class Component
{
public:
	Component(Game::Actor* owner) : _owner(owner) {}
	Component() : _owner(nullptr) {}

	Game::Actor* GetOwner() { return _owner; }

	void Attach(Game::Actor* owner) { _owner = owner; }

protected:
	Game::Actor* _owner;
};