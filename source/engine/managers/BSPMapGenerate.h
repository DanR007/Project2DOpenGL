#pragma once

#include <memory>
#include <vector>
#include <string>

#include <glm/vec2.hpp>


const uint64_t c_min_leaf_size = 15;
const uint64_t c_max_leaf_size = 35;

class GameManager;

class WallCreater
{
public:
	static std::pair<glm::vec2, glm::ivec2> GetWallSizeAndCoord(std::vector<std::string>& map, const glm::ivec2& start_coord, const glm::vec2& block_size)
	{
		glm::vec2 wall_size = block_size;
		glm::ivec2 wall_start = start_coord;
		int i = 1;
		char block_cell = 'B', wall_cell = 'W';
		map[start_coord.y][start_coord.x] = wall_cell;
		if (map[start_coord.y][start_coord.x + i] == block_cell)
		{
			//if wall horizontal change size
			while (map[start_coord.y][start_coord.x + i] == block_cell)
			{
				map[start_coord.y][start_coord.x + i] = wall_cell;
				i++;
			}
			wall_size = wall_size + glm::vec2(block_size.x * (i - 1), 0.f);

		}
		else
		{
			//if wall vertical then change start coordinate too
			while (map[start_coord.y - i][start_coord.x] == block_cell)
			{
				map[start_coord.y - i][start_coord.x] = wall_cell;
				i++;
				if (start_coord.y < i)
					break;
			}
			wall_size = wall_size + glm::vec2(0.f, block_size.y * (i - 1));
			wall_start = start_coord - glm::ivec2(0, i - 1);
		}
		return std::make_pair(wall_size, wall_start);
	}
};

class MapGenerator
{
public:
	
	MapGenerator();
	~MapGenerator();

	std::vector<std::string> StartGenerate(const glm::ivec2& map_size);

	void Destroy();
	void CreateNavMeshInRooms();
	void CreateHallNavMesh(const glm::ivec2& start, const glm::ivec2 size);

	glm::ivec2 GetCharacterPosition() const { return _character_position; }
	class Leaf
	{
	public:
		class Room
		{
		public:
			Room(const glm::ivec2& size, const glm::ivec2 position);

			glm::ivec2 GetPosition() const { return _position; }
			glm::ivec2 GetSize() const { return _size; }
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

		void CreateHorizontalHall(const int32_t& x1, const int32_t& x2, const int32_t& y);
		void CreateVerticalHall(const int32_t& y1, const int32_t& y2, const int32_t& x);
	private:
		glm::ivec2 _position, _size;
		Leaf* _left_leaf;
		Leaf* _right_leaf;

		Room* _room;

		const char free_cell = '.';
		const char wall_cell = 'B';
	};



private:
	GameManager* _manager;

	std::vector<Leaf*> leafs;
	std::vector<Leaf::Room*> _rooms;

	Leaf* g_root_leaf;

	std::vector<std::string> _map;

	glm::ivec2 _character_position = glm::ivec2(18, 21);

	friend class Leaf::Room;
	friend class Leaf;
};