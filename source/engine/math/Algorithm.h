#ifndef ALGORITHM
#define ALGORITHM

#include <glm/vec2.hpp>

#include <vector>
#include <math.h>
#include <queue>
#include <algorithm>

#include "../generators/RTSMapGenerator.h"

#include "../managers/EngineManager.h"
#include "../managers/GameManager.h"

#include "../AI/NavMesh.h"

class Algorithm
{
public:
    //получаем нужную нам позицию по компаратор который мы передадим
    //возвращает glm::ivec2(-1, -1) если не найдено подходящей позиции
    template<typename T>
        static glm::ivec2 BFS(const std::vector<std::vector<Cell*>>& map//карта по которой надо искать
                            , const glm::ivec2& start//начальная позиция
                            , const T& target//цель, которую надо найти
                            , bool (*cmp)(const T&,  Cell*)//компаратор, который проверяет совпадение цели со значением клетки
                            );

private:
    static inline int GetNodeCount(const glm::ivec2& start, const glm::ivec2& end) 
    {
        return std::abs(end.x - start.x) + std::abs(end.y - start.y);
    }
};

template<typename T>
glm::ivec2 Algorithm::BFS(
                        const std::vector<std::vector<Cell*>>& map
                        , const glm::ivec2& start
                        , const T& target
                        , bool (*cmp)(const T&, Cell*)
                        )
{
    Cell* current = map[start.y][start.x];

	std::queue<Cell*> q;
	std::vector<Cell*> cells;

	q.push(current);
	cells.push_back(current);

    std::vector<glm::ivec2> move =
                                {
                                    glm::ivec2(0, 1), glm::ivec2(0, -1),
                                    glm::ivec2(1, 0), glm::ivec2(-1, 0)
                                };

    const int size = move.size();

	while (!q.empty())
	{
		current = q.front();
		q.pop();

		for (int i = 0; i < size; ++i)
		{
			glm::ivec2 next = current->_position + move[i];

			if (GetEngine()->GetWorld()->GetNavMesh()->InMap(next))
			{
                Cell* map_cell = map[next.y][next.x];

				if (map_cell && cmp(target, map_cell))
				{
					return next;
				}
				else
				{
					std::vector<Cell*>::iterator it = std::find(cells.begin(), cells.end(), map_cell);
                    
					if (it == cells.end())
					{
						q.push(map_cell);
						cells.push_back(map_cell);
					}
				}
			}
		}
	}

    return glm::ivec2(-1, -1);
}

#endif//ALGORITHM