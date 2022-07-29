#pragma once

#include <glad/glad.h>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>


namespace Renderer
{
	class ShaderProgram
	{
	public:
		ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
		~ShaderProgram();

		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram& operator= (const ShaderProgram&) = delete;

		ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;
		ShaderProgram(ShaderProgram&& shaderProgram) noexcept;

		bool IsCompiled() const { return is_compiled; }
		void Use();
		void SetIn(const std::string& name, const GLint value);
		void SetMatrix4(const std::string& name, const glm::mat4& matrix);

		GLuint GetID() const { return ID; }
	private:

		GLuint ID;
		bool is_compiled;

		bool CreateShaderProgram(const GLenum& shaderType, const std::string& source_shader, GLuint& shaderID);
	};
}