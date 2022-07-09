#include "ResourcesManager.h"

#include "../renderer/ShaderRender.h"

#include <fstream>
#include <iostream>

ResourcesManager::ResourcesManager(const std::string& executablePath)
{
	size_t find = executablePath.find_last_of("/\\");

	exe_path = executablePath.substr(0, find);
}

std::shared_ptr<Renderer::ShaderProgram> ResourcesManager::LoadShaderPrograms(const std::string& shaderName, const std::string& fragmentPath, const std::string& vertexPath)
{

	return std::shared_ptr<Renderer::ShaderProgram>();
}

std::shared_ptr<Renderer::ShaderProgram> ResourcesManager::GetShaderProgram(const std::string& shaderName) const
{
	ShaderProgramMap::const_iterator it = shader_program_map.find(shaderName);

	if (it == shader_program_map.end())
	{
		std::cerr << "Can't find shader program: " + shaderName << std::endl;
		return nullptr;
	}

	return it->second;
}

std::string ResourcesManager::ReadShaderProgramFile(const std::string& path)
{
	std::ifstream file(exe_path + "/" + path, std::ios::in | std::ios::binary);

	std::string shaderSource, currentLine;

	if (!file.is_open())
	{
		std::cerr << "Shader file couldn't open or doesn't exist by this path: " + path << std::endl;
		return std::string();
	}

	std::getline(file, currentLine);
	shaderSource += currentLine + '\n';

	while (std::getline(file, currentLine))
	{
		shaderSource += currentLine;
	}

	return shaderSource;
}

