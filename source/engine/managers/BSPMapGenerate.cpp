#include "BSPMapGenerate.h"
#include "GameManager.h"

#include "../../game/gameobjects/WallActor.h"

#include <vector>

std::vector<std::shared_ptr<Leaf>> leafs;

std::shared_ptr<Leaf> rootLeaf = std::make_shared<Leaf>(glm::ivec2(0), glm::ivec2(5000, 2500));

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

	rootLeaf->CreateRooms();
}

void Leaf::CreateRooms()
{
	if (_left_leaf || _right_leaf)
	{
		if (_left_leaf)
			_left_leaf->CreateRooms();
		if (_right_leaf)
			_right_leaf->CreateRooms();

		if (_left_leaf && _right_leaf)
		{
			CreateHall(_left_leaf->GetRoom(), _right_leaf->GetRoom());
		}
	}
	else
	{
		glm::ivec2 roomSize = glm::ivec2(500 + std::rand() % (500 - _size.x - 100), 500 + std::rand() % (500 - _size.y - 100));
		glm::ivec2 roomCoord = glm::ivec2(10 + std::rand() % (_size.x - 10), 10 + std::rand() % (_size.y - 10));

		_room = std::make_shared<Room>(roomSize, roomCoord + _position);
	}
}

std::shared_ptr<Leaf::Room> Leaf::GetRoom()
{
	if (_room)
		return _room;
	else
	{
		std::shared_ptr<Room> leftRoom, rightRoom;
		if (_left_leaf)
			leftRoom = _left_leaf->GetRoom();
		if (_right_leaf)
			rightRoom = _right_leaf->GetRoom();

		if (!leftRoom && !rightRoom)
			return nullptr;
		else
			if (leftRoom)
				return leftRoom;
			else if (rightRoom)
				return rightRoom;
			else if (std::rand() % 2 == 0)
				return rightRoom;
			else
				return leftRoom;
	}
}

void Leaf::CreateHall(std::shared_ptr<Room> firstRoom, std::shared_ptr<Room> secondRoom)
{
	//glm::ivec2 firstPos = firstRoom->GetPosition(), firstSize = firstRoom->GetSize();
	//glm::ivec2 secondPos = secondRoom->GetPosition(), secondSize = secondRoom->GetSize();
	//
	//glm::ivec2 point1 = glm::ivec2(firstPos.x + 20 + (std::rand() % (firstSize.x - 40)), firstPos.y + 20 + (std::rand() % (firstSize.y - 40)));
	//glm::ivec2 point2 = glm::ivec2(secondPos.x + 20 + (std::rand() % (secondSize.x - 40)), secondPos.y + 20 + (std::rand() % (secondSize.y - 40)));


	//int w = point2.x - point1.x;
	//int h = point2.y - point1.y;

	//if (w < 0)
	//{
	//	if (h < 0)
	//	{
	//		if (std::rand() % 2 == 0)
	//		{
	//			GameManager::SpawnActor<Game::Objects::Wall>("wall", point2, glm::vec2(float(std::abs(w)), 10.f));
	//			GameManager::SpawnActor<Game::Objects::Wall>("wall", glm::vec2(point2) + glm::vec2(0.f, 80.f), glm::vec2(float(std::abs(w) - 80.f), 10.f));
	//			//halls.push(new Rectangle(point2.x, point1.y, Math.abs(w), 1));
	//			//halls.push(new Rectangle(point2.x, point2.y, 1, Math.abs(h)));
	//		}
	//		else
	//		{
	//			halls.push(new Rectangle(point2.x, point2.y, Math.abs(w), 1));
	//			halls.push(new Rectangle(point1.x, point2.y, 1, Math.abs(h)));
	//		}
	//	}
	//	else if (h > 0)
	//	{
	//		if (std::rand() % 2 == 0)
	//		{
	//			halls.push(new Rectangle(point2.x, point1.y, Math.abs(w), 1));
	//			halls.push(new Rectangle(point2.x, point1.y, 1, Math.abs(h)));
	//		}
	//		else
	//		{
	//			halls.push(new Rectangle(point2.x, point2.y, Math.abs(w), 1));
	//			halls.push(new Rectangle(point1.x, point1.y, 1, Math.abs(h)));
	//		}
	//	}
	//	else // если (h == 0)
	//	{
	//		halls.push(new Rectangle(point2.x, point2.y, Math.abs(w), 1));
	//	}
	//}
	//else if (w > 0)
	//{
	//	if (h < 0)
	//	{
	//		if (std::rand() % 2 == 0)
	//		{
	//			halls.push(new Rectangle(point1.x, point2.y, Math.abs(w), 1));
	//			halls.push(new Rectangle(point1.x, point2.y, 1, Math.abs(h)));
	//		}
	//		else
	//		{
	//			halls.push(new Rectangle(point1.x, point1.y, Math.abs(w), 1));
	//			halls.push(new Rectangle(point2.x, point2.y, 1, Math.abs(h)));
	//		}
	//	}
	//	else if (h > 0)
	//	{
	//		if (std::rand() % 2 == 0)
	//		{
	//			halls.push(new Rectangle(point1.x, point1.y, Math.abs(w), 1));
	//			halls.push(new Rectangle(point2.x, point1.y, 1, Math.abs(h)));
	//		}
	//		else
	//		{
	//			halls.push(new Rectangle(point1.x, point2.y, Math.abs(w), 1));
	//			halls.push(new Rectangle(point1.x, point1.y, 1, Math.abs(h)));
	//		}
	//	}
	//	else // если (h == 0)
	//	{
	//		halls.push(new Rectangle(point1.x, point1.y, Math.abs(w), 1));
	//	}
	//}
	//else // если (w == 0)
	//{
	//	if (h < 0)
	//	{
	//		halls.push(new Rectangle(point2.x, point2.y, 1, Math.abs(h)));
	//	}
	//	else if (h > 0)
	//	{
	//		halls.push(new Rectangle(point1.x, point1.y, 1, Math.abs(h)));
	//	}
	//}
}



