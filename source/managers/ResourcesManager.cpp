#include "ResourcesManager.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "../renderer/stb_image.h"
#include "../renderer/ShaderRender.h"
#include "../renderer/TextureRender.h"

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

std::shared_ptr<Renderer::Texture2D> ResourcesManager::LoadTexture(const std::string& textureName, const std::string& texturePath)
{
	int height = 0, width = 0, channels = 0;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* imageData = stbi_load(std::string(exe_path + "/" + texturePath).c_str(), &width, &height, &channels, 0);

	std::shared_ptr<Renderer::Texture2D> texture = 
		textures_map.emplace(textureName, std::make_shared<Renderer::Texture2D>(Renderer::Texture2D(imageData,
																									width,
																									height,
																									channels))).first->second;

	if (!texture)
	{
		std::cerr << "Cant load the texture: " + textureName << std::endl;
		return nullptr;
	}

	stbi_image_free(imageData);

	return texture;
}

std::shared_ptr<Renderer::Texture2D> ResourcesManager::GetTexture(const std::string& textureName)
{
	TexturesMap::const_iterator it = textures_map.find(textureName);

	if (it == textures_map.end())
	{
		std::cerr << "Cant find the texture: " + textureName << std::endl;
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

