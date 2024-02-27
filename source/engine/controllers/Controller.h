#pragma once

#include <memory>

#include <glm/vec2.hpp>


class Unit;
class AStarRTS;
class Goal;

struct Cell;

const glm::vec2 right_vector = glm::vec2(1.f, 0.f);
const glm::vec2 up_vector = glm::vec2(0.f, 1.f);

class Controller
{
public:
	Controller(Unit* controlledPawn, const float moveSpeed);
	Controller(const float moveSpeed);
	Controller();

	virtual ~Controller();
	virtual void Move(float deltaTime);

	/// @brief вызывается когда персонаж достиг одного из промежуточных узлов и готов получить 
	/// очередную цель
	/// @param map_coord новая цель движения
	void SetNewNode(const glm::ivec2& map_coord);
	inline void SetMoveSpeed(const float move_speed) { _move_speed = move_speed; }

	virtual void ChangeMoveVector(glm::vec2 inputVector);
	inline void ChangeNodePositionWindow(const glm::vec2 offset) { _node_coord += offset; }

	inline glm::vec2 GetMoveValue() { return _move_vector; }
	inline glm::vec2 GetNodeCoord() const { return _node_coord; }
	inline glm::ivec2 GetMapNode() const { return _node_in_map_coord; }

	inline bool GetPathComplete() const { return _complete_path; }
	//составляем путь к назначенной цели
	void MakePathForGoal(Cell* goal, const glm::ivec2& move_from);
protected:
	bool is_pause = false;
	bool _complete_path = true;

	float _move_speed;

	glm::vec2 _move_vector = glm::vec2(0.f);
	glm::vec2 _move_value  = glm::vec2(0.f);

	glm::ivec2 _node_in_map_coord;
	glm::vec2 _node_coord;

	Unit* _controlled_pawn;
	AStarRTS* _a_star;
private:
	
};