#pragma once

#include <vector>

#include <glm/vec2.hpp>

class Object
{
public:
	Object();

	/// @brief 
	/// @param startPosition 
	/// @param startSize 
	/// @param startRotation 
	Object(const glm::vec2& startPosition/*lower left point*/
		, const glm::vec2& startSize = glm::vec2(1.f)
		, const float startRotation = 0.f
		) : Object()
		{
			_world_position = startPosition;
			_size = startSize;
			_rotation = startRotation;
		}

	virtual ~Object();

	inline bool GetNeedToDestroy() const { return _need_to_destroy; }

	virtual void Destroy() 
	{
		_need_to_destroy = true;

		for (Object* obj : _attached_objects)
		{
			if(obj)
			{
				obj->Destroy();
			}
		}
	}

	inline glm::vec2 GetPosition() const { return _world_position; }
	inline glm::vec2 GetRelativePosition() const { return _relative_position; }
	inline float GetRotation() const { return _rotation; }
	inline glm::vec2 GetSize() const { return _size; }

	/// @brief выставить позицию в относительно размеров окна
	/// @param new_position 
	void SetPosition(const glm::vec2& new_position);
	/// @brief выставление размеров Actor
	/// @param new_size 
	void SetSize(const glm::vec2& new_size);
	void SetRotation(const float& new_rotation);
	void SetRelativePosition(const glm::vec2& new_position);

	void AddWorldPosition(const glm::vec2& d_pos);
	void AddWorldRotation(const float& d_rot);

	inline Object* GetOwner() const { return _owner; }

	/// @brief Привязка объекта к этому 
	/// @param obj объект, который мы хотим привязать
	inline void Attach(Object* obj) 
	{
		_attached_objects.push_back(obj);
		obj->_owner = this;
	}

	/// @brief Привязка объекта
	/// @param obj объект, к которому мы хотим привязать
	inline void AttachTo(Object* obj) 
	{
		obj->Attach(this);
	}

	inline glm::vec2 GetXAxis() const { return _x_axis; }
	inline glm::vec2 GetYAxis() const { return _y_axis; }

	/// @brief возвращает все привязанные объекты
	/// @return массив привязанных объектов
	std::vector<Object*> GetChildObjects() const { return _attached_objects; }
protected:
	glm::vec2 _x_axis = glm::vec2(1.f, 0.f), _y_axis = glm::vec2(0.f, 1.f);

	void Rotate();
	void SetNeedToDestroy() { _need_to_destroy = true; }

	bool _need_to_destroy;

	glm::vec2 _world_position, _relative_position;
	glm::vec2 _size;
	float _rotation;

	/// @brief объекты которые привязаны к этому
	std::vector<Object*> _attached_objects;

	Object* _owner = nullptr;
};