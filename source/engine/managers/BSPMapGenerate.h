#pragma once

#include <memory>
#include <vector>
#include <string>

#include <glm/vec2.hpp>


const uint64_t c_min_leaf_size = 5;
const uint64_t c_max_leaf_size = 15;

class MapGenerator
{
public:
	
	MapGenerator();
	~MapGenerator();

	std::vector<std::string> StartGenerate(const glm::ivec2& map_size);

	void Destroy();

	glm::ivec2 GetCharacterPosition() const { return _character_position; }
	class Leaf
	{
	public:
		class Room
		{
		public:
			Room(const glm::ivec2& size, const glm::ivec2 position);

			glm::ivec2 GetPosition() { return _position; }
			glm::ivec2 GetSize() { return _size; }
		private:
			glm::ivec2 _position;
			glm::ivec2 _size;
		};

		Leaf(const glm::ivec2& position, const glm::ivec2& size);
		~Leaf();

		bool CreateNewLeaf();
		void Split();

		void CreateRooms();
		Room* GetRoom();

		void CreateHall(Room* firstRoom, Room* secondRoom);
	private:
		glm::ivec2 _position, _size;
		Leaf* _left_leaf;
		Leaf* _right_leaf;

		Room* _room;

	};



private:
	std::vector<Leaf*> leafs;
	std::vector<Leaf::Room*> _rooms;

	Leaf* g_root_leaf;

	std::vector<std::string> _map;

	glm::ivec2 _character_position;

	friend class Leaf::Room;
	friend class Leaf;
};