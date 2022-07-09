#pragma once

#include <string>
#include <memory>
#include <map>

namespace Renderer
{
	class ShaderProgram;
}

class ResourcesManager
{
public:
	ResourcesManager(const std::string& executablePath);

	std::shared_ptr<Renderer::ShaderProgram> LoadShaderPrograms(const std::string& shaderName, const std::string& fragmentPath, const std::string& vertexPath);
	std::shared_ptr<Renderer::ShaderProgram> GetShaderProgram(const std::string& shaderName) const;
private:
	std::string ReadShaderProgramFile(const std::string& path);
	std::string exe_path;

	typedef std::map<std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramMap;
	ShaderProgramMap shader_program_map;
};