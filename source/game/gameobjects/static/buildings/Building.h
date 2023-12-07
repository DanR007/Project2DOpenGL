#pragma once

#include <map>

#include "../../../../engine/default_classes/Pawn.h"

#include "BuildingTypes.h"

class Worker;

/// @brief здание
class Building : public Pawn
{
public:
	/// @brief конструктор
	/// @param pivot_position позиция пивота на карте 
	/// @param size размер здания в занятых позиций на карте
	/// @param type тип здания
	Building(const glm::ivec2& pivot_position, const glm::ivec2& size, const EBuildingType& type);
	~Building();

	/// @brief размещение здания на карте (виртуальный метод)
	virtual void Replace();
	/// @brief размещено ли здание
	/// @return 
	bool GetIsReplaced() const { return _replace; }
	glm::ivec2 GetBuildingSize() const { return _building_size;	}
	/// @brief можно ли раместить здание
	/// @return 
	bool CanReplace();

	virtual void Update(const float& deltaTime) override;
protected:
	/// @brief приватный конструктор
	/// @param initSubtextureName название subtexture
	/// @param startPosition начальная позиция в оконных координатах
	/// @param startSize размер спрайта
	/// @param render_layer слой рендера
	/// @param startRotation начальный поворот
	Building(const std::string& initSubtextureName
		, const glm::vec2& startPosition/*lower left point*/
		, const glm::vec2& startSize = glm::vec2(1.f)
		, const uint8_t& render_layer = 0
		, const float startRotation = 0.f);
	/// @brief работник в здании если nullptr то его нет
	Worker* _worker = nullptr;
	/// @brief размер здания
	glm::ivec2 _building_size;
	/// @brief тип здания
	EBuildingType _type;
	/// @brief переменная размещения
	bool _replace = false;
};