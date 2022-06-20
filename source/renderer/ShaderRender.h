#pragma once

#include <glad/glad.h>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>


namespace Renderer
{
	class ShaderProgram
	{
		ShaderProgram(const std::string& verteShader, const std::string& fragmentShader);
	};
}