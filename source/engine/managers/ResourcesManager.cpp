#include "ResourcesManager.h"
#include "RenderManager.h"
#include "EngineManager.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "../renderer/stb_image.h"
#include "../renderer/ShaderRender.h"
#include "../renderer/TextureRender.h"
#include "../renderer/Sprite.h"
#include "../renderer/AnimSprite.h"

#include <fstream>
#include <iostream>

ResourcesManager::~ResourcesManager()
{
	shader_program_map.clear();
	textures_map.clear();
	exe_path.~basic_string();
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

std::shared_ptr<Renderer::ShaderProgram> ResourcesManager::GetShaderProgram(const std::string& shaderName)
{
	ShaderProgramMap::const_iterator it = shader_program_map.find(shaderName);

	if (it == shader_program_map.end())
	{
		std::cerr << "Can't find shader program: " + shaderName << std::endl;
		return nullptr;
	}

	return it->second;
}

std::shared_ptr<Renderer::Texture2D> ResourcesManager::LoadTexture(const std::string& textureName, const std::string& texturePath, const GLuint& layer_count)
{
	int height, width, channels = 0;

	stbi_set_flip_vertically_on_load(true);

	std::string path = exe_path + "/" + texturePath;

	unsigned char* imageData = stbi_load(path.c_str(), &width, &height, &channels, 0);

	std::shared_ptr<Renderer::Texture2D> texture = textures_map.emplace(textureName, std::make_shared<Renderer::Texture2D>(Renderer::Texture2D(imageData,
			width,
			height / layer_count,
			channels, GL_REPEAT, GL_NEAREST, layer_count))).first->second;
	

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

std::shared_ptr<Renderer::Texture2D> ResourcesManager::LoadTextureAtlas(const std::string& textureName, const std::string& texturePath,
	const std::vector<std::string>& subTextureNamesArr,
	const std::vector<uint8_t>& subTextureSizeArr, const GLuint& layer_count)
{

	auto texture = LoadTexture(textureName, texturePath, layer_count);

	if (texture)
	{
		const unsigned int textureWidth = texture->GetWidth();
		const unsigned int textureHeight = texture->GetHeight();
		unsigned int offsetX = 0;
		int offsetY = textureHeight;
		GLuint cur_layer = layer_count - 1;
		for (int i = 0; i < subTextureNamesArr.size(); i++)
		{
			if (i > 0 && subTextureSizeArr[i] != subTextureSizeArr[i - 1])
			{
				cur_layer--;
			}

			glm::vec2 leftBottomUV(static_cast<float>((float)offsetX / (float)textureWidth), static_cast<float>((float)(offsetY - subTextureSizeArr[i]) / (float)textureHeight));
			glm::vec2 rightTopUV(static_cast<float>((float)(offsetX + subTextureSizeArr[i]) / (float)textureWidth), static_cast<float>((float)offsetY / (float)textureHeight));

			texture->AddSubTexture(subTextureNamesArr[i], leftBottomUV, rightTopUV, cur_layer);

			offsetX += subTextureSizeArr[i];
			if (offsetX >= textureWidth)
			{
				offsetX = 0;
				offsetY -= subTextureSizeArr[i];
			}
		}
	}
	return texture;
}

void ResourcesManager::LoadAll(const std::string& executablePath)
{
	std::size_t find;
	#ifndef __linux__
	find = executablePath.find_last_of("/\\");
	#else
	find = executablePath.find_last_of("/");

	#endif // ifndef __linux__
	exe_path = executablePath.substr(0, find);

	LoadShaderPrograms("spriteShader", SPRITE_FRAGMENT_SHADER_PATH, SPRITE_VERTEX_SHADER_PATH);
	

	glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(window_size.x), 0.f, static_cast<float>(window_size.y), -100.f, 100.f);

	GetShaderProgram("spriteShader")->Use();
	GetShaderProgram("spriteShader")->SetIn("tex", 0);
	GetShaderProgram("spriteShader")->SetMatrix4("projectionMat", projectionMatrix);
	std::vector<std::string> names_texture_atlas = { "mush1", "mush2", "mush3", "wall", "goal", "selected", "pistolBullet", "tree", "stone",
										"ground", "water", "lumber", "barracks", "quarry", "emptyProgressBar", "fullProgressBar"};

	std::vector<std::string> font_names;
	for (int i = 0; i < 26; i++)
	{
		std::string s = "a";
		s[0] += i;
		names_texture_atlas.push_back(s);
	}
	for (int i = 0; i < 10; i++)
	{
		std::string s = "0";
		s[0] += i;
		names_texture_atlas.push_back(s);
	}
	names_texture_atlas.push_back("background");
	names_texture_atlas.push_back(" ");

	std::vector<std::string> special_signs = {"/", "\\", "[", "]", ":", "+", "-", ".", ","};
	for(std::string s : special_signs)
	{
		names_texture_atlas.push_back(s);
	}
	
	while (names_texture_atlas.size() != 80)
	{
		names_texture_atlas.push_back("");
	}

	std::vector<uint8_t> sprites_size;
	
	for (int i = 0; i < 16; i++)
	{
		sprites_size.push_back(16);
	}
	for (int i = 0; i < 64; i++)
	{
		sprites_size.push_back(8);
	}

	LoadTextureAtlas("textureAtlas", "resources/textures/mushroom.png", names_texture_atlas, sprites_size, GLuint(2));
}