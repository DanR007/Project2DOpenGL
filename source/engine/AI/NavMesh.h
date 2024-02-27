#pragma once
#include <glm/vec2.hpp>
#include <vector>

#include "../generators/RTSMapGenerator.h"

struct Cell;

enum class EResourceTypes;

class Resource;

class NavMeshRTS
{
public:
	/// @brief конструктор
	/// @param map карта
	NavMeshRTS(std::vector<std::vector<Cell*>> map);
	NavMeshRTS();

	~NavMeshRTS();
	/// @brief заполнение карты если конструктор вызывался без карты
	/// @param map карта
	void FillMap(std::vector<std::vector<Cell*>> map);
	/// @brief получить карту
	/// @return 
	std::vector<std::vector<Cell*>> GetMap();
	/// @brief очистка клетки и создание там пустой
	/// @param position позиция очищаемой клетки
	void ClearMapCell(const glm::ivec2& position);
	/// @brief выставить в клетку символ
	/// @param position позиция клетки
	/// @param symbol какой символ выставить
	/// @param actor тот кто занимает эту клетку
	void SetMapCell(const glm::ivec2& position, const char& symbol, Actor* actor);
	/// @brief вывод островов на карте
	void PrintMap();

	bool InMap(const glm::ivec2& pos);

	Resource* GetNearestResource(const glm::ivec2& position, const EResourceTypes& type);

	bool IsFreeCell(const glm::ivec2& pos) { return InMap(pos) && _map[pos.y][pos.x]->_symbol == _free_cell; }

	void RefillAllID();

private:
	void RefillIDInBreadth(const glm::ivec2& start, unsigned short int id);
	void ResetMapID();
	
	const char _free_cell = '.'; 


	std::vector<std::vector<Cell*>> _map;

	friend class AStarRTS;
};