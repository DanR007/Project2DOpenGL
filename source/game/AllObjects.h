#pragma once

#include <vector>
#include <memory>

namespace Game
{
	class Actor;
	class Pawn;
	class MainCharacter;
}

extern std::vector<std::shared_ptr<Game::Actor>> all_actors;
extern std::vector<std::shared_ptr<Game::Pawn>> all_pawns;
extern std::shared_ptr<Game::MainCharacter> main_character;