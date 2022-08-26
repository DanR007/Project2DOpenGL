#include "BSPMapGenerate.h"
#include <vector>

std::vector<std::shared_ptr<Leaf>> leafs;

std::shared_ptr<Leaf> rootLeaf = std::make_shared<Leaf>(glm::ivec2(0), glm::ivec2(5000, 5000));

Leaf::Leaf(const glm::ivec2& position, const glm::ivec2& size)
	: _position(position), _size(size)
{

}

bool Leaf::CreateNewLeaf()
{
	if (_left_leaf || _right_leaf)
		return false;

	bool splitH = std::rand() % 2 == 0;

	if (float(_size.x) / float(_size.y) >= 1.25f)
	{
		splitH = true;
		if(_size.x <= c_min_leaf_size)
			return false;
	}
	else
		if (float(_size.y) / float(_size.x) >= 1.25f)
		{
			splitH = false;
			if (_size.y <= c_min_leaf_size)
				return false;
		}

	int max = std::max(_size.x, _size.y);
	int splitSize = c_min_leaf_size + std::rand() % (max - c_min_leaf_size);

	if (splitH)
	{
		_left_leaf = std::make_shared<Leaf>(_position, glm::ivec2(_size.x, splitSize));
		_right_leaf = std::make_shared<Leaf>(glm::ivec2(_position.x, _position.y + splitSize),
			glm::ivec2(_size.x, _size.y - splitSize));
	}
	else
	{
		_left_leaf = std::make_shared<Leaf>(_position, glm::ivec2(splitSize, _size.y));
		_right_leaf = std::make_shared<Leaf>(glm::ivec2(_position.x + splitSize, _position.y),
			glm::ivec2(_size.x - splitSize, _size.y));
	}

	return true;
}

void Leaf::Split()
{
	leafs.push_back(rootLeaf);
	bool splited = true;
	while (splited)
	{
		splited = false;
		for (std::shared_ptr<Leaf> l : leafs)
		{
			if (!l->_left_leaf && !l->_right_leaf)
			{
				bool randPercent = std::rand() % 4 < 3;
				if (l->_size.x > c_max_leaf_size || l->_size.y > c_max_leaf_size || randPercent)
				{
					if (l->CreateNewLeaf())
					{
						leafs.push_back(l->_left_leaf);
						leafs.push_back(l->_right_leaf);
						splited = true;
					}
				}
			}
		}
	}
}



