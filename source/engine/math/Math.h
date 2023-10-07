#pragma once
#include <glm/vec2.hpp>

#include <cmath>

class Math
{
public:
	static float VM(const glm::vec2& a, const glm::vec2& b)
	{
		return a.x * b.y - a.y * b.x;
	}
	static float DOT(const glm::vec2& a, const glm::vec2& b)
	{
		return a.x * b.x + a.y * b.y;
	}
	static float Length(const glm::vec2& a)
	{
		return std::sqrt(std::pow(a.x, 2) + std::pow(a.y, 2));
	}
};