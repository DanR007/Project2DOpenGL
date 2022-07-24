#include "ResourcesManager.h"

#include "../renderer/ShaderRender.h"

#include <fstream>
#include <iostream>

ResourcesManager::ResourcesManager(const std::string& executablePath)
{
	std::size_t find = executablePath.find_last_of("/\\");

	exe_path = executablePath.substr(0, find);
}

std::shared_ptr<Renderer::ShaderProgram> ResourcesManager::LoadShaderPrograms(const std::string& shaderName, const std::string& fragmentPath, const std::string& vertexPath)
{
	std::string vertexSource = ReadShaderProgramFile(vertexPath);
	std::string fragmentSource = ReadShaderProgramFile(fragmentPath);

	if (vertexSource.empty())
	{
		std::cerr << "Vertrex shader by this path are empty: " + vertexPath << std::endl;
		return nullptr;
	}

	if (fragmentSource.empty())
	{
		std::cerr << "Fragment shader by this path are empty: " + fragmentPath << std::endl;
		return nullptr;
	}


	std::shared_ptr<Renderer::ShaderProgram> shaderProgram = shader_program_map.emplace(shaderName, std::make_shared<Renderer::ShaderProgram>(vertexSource, fragmentSource)).first->second;

	if (shaderProgram->IsCompiled())
	{

		return shaderProgram;
	}

	std::cerr << "Program are not compile \n Vertex program: " + vertexPath + "\n Fragment program: " + fragmentPath << std::endl;
	return nullptr;
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

