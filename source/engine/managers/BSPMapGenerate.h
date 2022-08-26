#pragma once

#include <memory>

#include <glm/vec2.hpp>

const uint64_t c_min_leaf_size = 500;
const uint64_t c_max_leaf_size = 1000;


class Leaf
{
public:
	class Room
	{

	};

	Leaf(const glm::ivec2& position, const glm::ivec2& size);

	bool CreateNewLeaf();
	void Split();
private:
	glm::ivec2 _position, _size;
	std::shared_ptr<Leaf> _left_leaf, _right_leaf;
};