#pragma once

#include <memory>

#include <glm/vec2.hpp>

const uint64_t c_min_leaf_size = 700;
const uint64_t c_max_leaf_size = 1500;


class Leaf
{
public:
	class Room
	{
	public:
		Room(const glm::ivec2& size, const glm::ivec2 position)
			:_size(size), _position(position)
		{

		}

		glm::ivec2 GetPosition() { return _position; }
		glm::ivec2 GetSize() { return _size; }
	private:
		glm::ivec2 _position;
		glm::ivec2 _size;
	};

	Leaf(const glm::ivec2& position, const glm::ivec2& size);

	bool CreateNewLeaf();
	void Split();

	void CreateRooms();
	std::shared_ptr<Room> GetRoom();

	void CreateHall(std::shared_ptr<Room> firstRoom, std::shared_ptr<Room> secondRoom);
private:
	glm::ivec2 _position, _size;
	std::shared_ptr<Leaf> _left_leaf, _right_leaf;

	std::shared_ptr<Room> _room;
};