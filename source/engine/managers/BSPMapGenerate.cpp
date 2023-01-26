#include "BSPMapGenerate.h"
#include "GameManager.h"

#include "../../main.h"

#include "../../game/gameobjects/WallActor.h"

#include <iostream>

MapGenerator* generator;

MapGenerator::MapGenerator()
{
	generator = this;
	_manager = GetWorld();
}

MapGenerator::~MapGenerator()
{
	
}

MapGenerator::Leaf::Leaf(const glm::ivec2& position, const glm::ivec2& size)
	: _position(position), _size(size)
{
	_left_leaf = nullptr;
	_right_leaf = nullptr;

	_room = nullptr;
}

MapGenerator::Leaf::~Leaf()
{
	delete _room;
	_room = nullptr;
}

bool MapGenerator::Leaf::CreateNewLeaf()
{
	if (_left_leaf || _right_leaf)
		return false;

	bool split_h = std::rand() % 2 == 0;

	if (float(_size.x) / float(_size.y) >= 1.25f)
	{
		split_h = false;
		if(_size.x <= c_min_leaf_size)
			return false;
	}
	else
		if (float(_size.y) / float(_size.x) >= 1.25f)
		{
			split_h = true;
			if (_size.y <= c_min_leaf_size)
				return false;
		}

	int max = std::max(_size.x, _size.y) - c_min_leaf_size;
	int split_size;
	if (max - c_min_leaf_size > 0)
		split_size = c_min_leaf_size + std::rand() % (max - c_min_leaf_size);
	else
		if(max - c_min_leaf_size == 0)
		split_size = c_min_leaf_size;

	if (split_h)
	{
		_left_leaf = new Leaf(_position, glm::ivec2(_size.x, split_size));
		_right_leaf = new Leaf(glm::ivec2(_position.x, _position.y + split_size),
			glm::ivec2(_size.x, _size.y - split_size));
	}
	else
	{
		_left_leaf = new Leaf(_position, glm::ivec2(split_size, _size.y));
		_right_leaf = new Leaf(glm::ivec2(_position.x + split_size, _position.y),
			glm::ivec2(_size.x - split_size, _size.y));
	}

	return true;
}

void MapGenerator::Leaf::Split()
{
	generator->leafs.push_back(generator->g_root_leaf);
	bool splited = true;
	while (splited)
	{
		splited = false;

		for (int i = 0; i < generator->leafs.size(); i++)
		{
			Leaf* l = generator->leafs[i];
			if (!l->_left_leaf && !l->_right_leaf)
			{
				bool rand_percent = std::rand() % 4 < 3;
				if ((l->_size.x > c_max_leaf_size || l->_size.y > c_max_leaf_size) && rand_percent)
				{
					if (l->CreateNewLeaf())
					{
						if(l->_left_leaf)
						generator->leafs.push_back(l->_left_leaf);
						if(l->_right_leaf)
						generator->leafs.push_back(l->_right_leaf);
						splited = true;
					}
				}
			}
		}
	}

	generator->g_root_leaf->CreateRooms();
}

void MapGenerator::Leaf::CreateRooms()
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
	{//10 min_leaf_size
		glm::ivec2 room_size = glm::ivec2(5 + std::rand() % (_size.x - 7), 5 + std::rand() % (_size.y - 7));
		glm::ivec2 room_coord = glm::ivec2(1 + std::rand() % (_size.x - room_size.x - 1), 1 + std::rand() % (_size.y - room_size.y - 1));

		_room = new Room(room_size, room_coord + _position);

		generator->_rooms.push_back(_room);
	}
}

MapGenerator::Leaf::Room* MapGenerator::Leaf::GetRoom()
{
	if (_room)
		return _room;
	else
	{
		Room* left_room, *right_room;
		if (_left_leaf)
			left_room = _left_leaf->GetRoom();
		if (_right_leaf)
			right_room = _right_leaf->GetRoom();

		if (!left_room && !right_room)
			return nullptr;
		else
			if (left_room)
				return left_room;
			else if (right_room)
				return right_room;
			else if (std::rand() % 2 == 0)
				return right_room;
			else
				return left_room;
	}
}

void MapGenerator::Leaf::CreateHall(Room* first_room, Room* second_room)
{
	glm::ivec2 first_pos = first_room->GetPosition(), first_size = first_room->GetSize();
	glm::ivec2 second_pos = second_room->GetPosition(), second_size = second_room->GetSize();

	glm::ivec2 point1 = glm::ivec2(first_pos.x + 1 + (std::rand() % (first_size.x - 1)), first_pos.y + 1 + (std::rand() % (first_size.y - 1)));
	glm::ivec2 point2 = glm::ivec2(second_pos.x + 1 + (std::rand() % (second_size.x - 1)), second_pos.y + 1 + (std::rand() % (second_size.y - 1)));

	int w = point2.x - point1.x;
	int h = point2.y - point1.y;

	if (w < 0)
	{
		if (h < 0)
		{
			if (std::rand() % 2 == 0)
			{
				/*
				*		p1
				*		0
				p2OOOOOOO
				*/
				CreateVerticalHall(point2.y, point1.y, point1.x);
				CreateHorizontalHall(point2.x, point1.x, point2.y);
			}
			else
			{
				/*
				*
				00000000000p1
				0
				p2
				*/
				CreateVerticalHall(point2.y, point1.y, point2.x);
				CreateHorizontalHall(point2.x, point1.x, point1.y);
			}
		}
		else if (h > 0)
		{
			if (std::rand() % 2 == 0)
			{
				/*
				p2 OOOOOOO
						 O
				        p1
				*/
				CreateVerticalHall(point1.y, point2.y, point1.x);
				CreateHorizontalHall(point2.x, point1.x, point2.y);
			}
			else
			{
				/*
				p2 O
				   OOOOOOp1
				*/
				CreateVerticalHall(point1.y, point2.y, point2.x);
				CreateHorizontalHall(point2.x, point1.x, point1.y);
			}
		}
		else // если (h == 0)
		{
			/*
			p2 OOOOOOOOO p1
			*/
			CreateHorizontalHall(point2.x, point1.x, point1.y);
		}
	}
	else if (w > 0)
	{
		if (h < 0)
		{
			if (std::rand() % 2 == 0)
			{
				/*
				p1 OOOOOOOOOO
							O
							p2
				*/
				CreateVerticalHall(point2.y, point1.y, point2.x);
				CreateHorizontalHall(point1.x, point2.x, point1.y);
			}
			else
			{
				/*
				   OOOOOOOOOOp2
				   O		
				p1 O
				*/
				CreateVerticalHall(point2.y, point1.y, point1.x);
				CreateHorizontalHall(point1.x, point2.x, point2.y);
			}
		}
		else if (h > 0)
		{
			if (std::rand() % 2 == 0)
			{
				/*
							p2
							O
				p1 OOOOOOOOOO
				*/

				CreateVerticalHall(point1.y, point2.y, point1.x);
				CreateHorizontalHall(point1.x, point2.x, point2.y);
			}
			else
			{
				/*
				   OOOOOOOOOOp2
				   O
				p1 O
				*/
				CreateVerticalHall(point1.y, point2.y, point2.x);
				CreateHorizontalHall(point1.x, point2.x, point1.y);
			}
		}
		else // если (h == 0)
		{
			/*
			p1 OOOOOOOOO p2
			*/
			CreateHorizontalHall(point1.x, point2.x, point1.y);

		}
	}
	else // если (w == 0)
	{
		if (h < 0)
		{
			CreateVerticalHall(point2.y, point1.y, point1.x);
		}
		else if (h > 0)
		{
			CreateVerticalHall(point1.y, point2.y, point1.x);
		}
	}

	
}

void MapGenerator::Leaf::CreateHorizontalHall(const int32_t& x1, const int32_t& x2, const int32_t& y)
{
	for (int32_t i = x1 - 1; i <= x2 + 1; i++)
	{
		if(i <= x2 && i >= x1)
		generator->_map[y][i] = free_cell;
		if (generator->_map[y - 1][i] != free_cell)
			generator->_map[y - 1][i] = wall_cell;
		if (generator->_map[y + 1][i] != free_cell)
			generator->_map[y + 1][i] = wall_cell;
	}
}
void MapGenerator::Leaf::CreateVerticalHall(const int32_t& y1, const int32_t& y2, const int32_t& x)
{
	for (int32_t i = y1; i <= y2; i++)
	{
		generator->_map[i][x] = free_cell;
		if (generator->_map[i][x - 1] != free_cell)
			generator->_map[i][x - 1] = wall_cell;
		if (generator->_map[i][x + 1] != free_cell)
			generator->_map[i][x + 1] = wall_cell;
	}
}

MapGenerator::Leaf::Room::Room(const glm::ivec2& size, const glm::ivec2 position)
	:_size(size), _position(position)
{
	char free_cell = '.', wall_cell = 'B';
	for (int32_t i = _position.y; i < _position.y + _size.y; i++)
	{
		for (int32_t j = _position.x - 1; j < _position.x + _size.x + 1; j++)
		{
			generator->_map[i][j] = free_cell;
			if(i == _position.y)
				generator->_map[i - 1][j] = wall_cell;
			else
				if (i == _position.y + _size.y - 1)
				{
					generator->_map[i + 1][j] = wall_cell;
				}
		}
		generator->_map[i][_position.x - 1] = wall_cell;
		generator->_map[i][_position.x + _size.x] = wall_cell;
	}
}

std::vector<std::string> MapGenerator::StartGenerate(const glm::ivec2& map_size)
{
	_map.resize(map_size.y + 2);
	for (int32_t i = 0; i < map_size.y + 2; i++)
		for(int32_t j = 0; j < map_size.y + 2; j++)
		_map[i] += 'O';

	g_root_leaf = new Leaf(glm::ivec2(0), map_size);
	g_root_leaf->Split();

	generator = nullptr;
	Leaf::Room* character_room = _rooms[std::rand() % _rooms.size()];
	_character_position = character_room->GetPosition() + glm::ivec2(std::rand() % character_room->GetSize().x, std::rand() % character_room->GetSize().y);
	//_map[_character_position.y][_character_position.x] = 'P';
	for (int32_t i = 0; i < map_size.y + 2; i++)
		std::cout << _map[i] << std::endl;

	return _map;
}

void MapGenerator::Destroy()
{
	for (Leaf* l : leafs)
	{
		if (l)
			delete l;
	}
	delete this;
}

void MapGenerator::CreateNavMeshInRooms()
{
	NavMesh* nav_mesh = _manager->GetNavMesh();
	glm::vec2 block_size = _manager->GetBlockSize();
	glm::vec2 offset = _manager->GetOffset();
	for (Leaf::Room* room : _rooms)
	{
		glm::vec2 position = glm::vec2(-(_character_position.x - room->GetPosition().x) * block_size.x + offset.x,
			(_character_position.y - room->GetPosition().y) * block_size.y + offset.y);
		//nav_mesh->AddRectangleArea(position, glm::vec2(room->GetSize().x * block_size.x, room->GetSize().y * block_size.y));
	}
}

void MapGenerator::CreateHallNavMesh(const glm::ivec2& start, const glm::ivec2 size)
{
	NavMesh* nav_mesh = _manager->GetNavMesh();
	glm::vec2 block_size = _manager->GetBlockSize();
	glm::vec2 offset = _manager->GetOffset();

	glm::vec2 position = glm::vec2(-(_character_position.x - start.x) * block_size.x + offset.x,
		(_character_position.y - start.y) * block_size.y + offset.y);
	//nav_mesh->AddRectangleArea(position, glm::vec2(size.x * block_size.x, size.y * block_size.y));
}
