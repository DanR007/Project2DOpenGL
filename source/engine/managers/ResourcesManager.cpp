#include "ResourcesManager.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "../renderer/stb_image.h"
#include "../renderer/ShaderRender.h"
#include "../renderer/TextureRender.h"
#include "../renderer/Sprite.h"
#include "../renderer/AnimSprite.h"

#include <fstream>
#include <iostream>

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

std::shared_ptr<Renderer::Texture2D> ResourcesManager::LoadTexture(const std::string& textureName, const std::string& texturePath)
{
	int height, width, channels = 0;

	stbi_set_flip_vertically_on_load(true);

	std::string path = exe_path + "/" + texturePath;

	unsigned char* imageData = stbi_load(path.c_str(), &width, &height, &channels, 0);
	
	std::shared_ptr<Renderer::Texture2D> texture = 
		textures_map.emplace(textureName, std::make_shared<Renderer::Texture2D>(Renderer::Texture2D(imageData,
																									width,
																									height,
																									channels, GL_REPEAT))).first->second;

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
	const unsigned int width, const unsigned int height)
{

	auto texture = LoadTexture(textureName, texturePath);

	if (texture)
	{
		const unsigned int textureWidth = texture->GetWidth();
		const unsigned int textureHeight = texture->GetHeight();
		unsigned int offsetX = 0;
		unsigned int offsetY = textureHeight;
		for (auto& currentSubTextureName : subTextureNamesArr)
		{
			glm::vec2 leftBottomUV(static_cast<float>((float)offsetX / (float)textureWidth), static_cast<float>((float)(offsetY - height) / (float)textureHeight));
			glm::vec2 rightTopUV(static_cast<float>((float)(offsetX + width) / (float)textureWidth), static_cast<float>((float)offsetY / (float)textureHeight));

			texture->AddSubTexture(currentSubTextureName, leftBottomUV, rightTopUV);

			offsetX += width;
			if (offsetX >= textureWidth)
			{
				offsetX = 0;
				offsetY -= height;
			}

		}
	}
	return texture;
}


std::shared_ptr<Renderer::Sprite> ResourcesManager::LoadSprite(const std::string& spriteName,
	const std::string& textureName,
	const std::string& shaderName,
	const unsigned int spriteWidth,
	const unsigned int spriteHeight,
	const std::string& subTextureName)
{
	auto l_texture = GetTexture(textureName);
	if (!l_texture)
	{
		std::cerr << "Cant find texture (" + textureName + ")  for the sprite " + spriteName << std::endl;
	}

	auto l_shader = GetShaderProgram(shaderName);
	if (!l_shader)
	{
		std::cerr << "Cant find shader (" + shaderName + ")  for the sprite " + spriteName << std::endl;
	}

	std::shared_ptr<Renderer::Sprite> newSprite = sprites_map.emplace(textureName, std::make_shared<Renderer::Sprite>(l_texture, l_shader, subTextureName, nullptr,
		glm::vec2(0.f, 0.f),
		glm::vec2(spriteWidth, spriteHeight))).first->second;

	return newSprite;
}

std::shared_ptr<Renderer::Sprite> ResourcesManager::GetSprite(const std::string& spriteName)
{
	SpritesMap::const_iterator it = sprites_map.find(spriteName);

	if (it == sprites_map.end())
	{
		std::cerr << "Cant find the sprite: " + spriteName << std::endl;
		return nullptr;
	}
	
	return it->second;
}

std::shared_ptr<Renderer::AnimSprite> ResourcesManager::LoadAnimSprite(const std::string& spriteName,
	const std::string& textureName,
	const std::string& shaderName,
	const unsigned int spriteWidth,
	const unsigned int spriteHeight,
	const std::string& subTextureName)
{
	auto l_texture = GetTexture(textureName);
	if (!l_texture)
	{
		std::cerr << "Cant find texture (" + textureName + ")  for the sprite " + spriteName << std::endl;
	}

	auto l_shader = GetShaderProgram(shaderName);
	if (!l_shader)
	{
		std::cerr << "Cant find shader (" + shaderName + ")  for the sprite " + spriteName << std::endl;
	}

	std::shared_ptr<Renderer::AnimSprite> newSprite = anim_sprites_map.emplace(spriteName, std::make_shared<Renderer::AnimSprite>(l_texture, l_shader, subTextureName, nullptr,
		glm::vec2(0.f, 0.f),
		glm::vec2(spriteWidth, spriteHeight))).first->second;

	return newSprite;
}

std::shared_ptr<Renderer::AnimSprite> ResourcesManager::GetAnimSprite(const std::string& animSpriteName)
{
	AnimSpritesMap::const_iterator it = anim_sprites_map.find(animSpriteName);

	if (it == anim_sprites_map.end())
	{
		std::cerr << "Cant find the anim sprite: " + animSpriteName << std::endl;
		return nullptr;
	}

	return it->second;
}

void ResourcesManager::LoadAll(const std::string& executablePath)
{
	std::size_t find = executablePath.find_last_of("/\\");

	exe_path = executablePath.substr(0, find);

	LoadShaderPrograms("texture", TEXTURE_FRAGMENT_SHADER_PATH, TEXTURE_VERTEX_SHADER_PATH);
	LoadShaderPrograms("spriteShader", SPRITE_FRAGMENT_SHADER_PATH, SPRITE_VERTEX_SHADER_PATH);

	std::vector<std::string> names = { "mush1", "mush2", "mush3", "wall","goal", "selected", "pistolBullet","tree","stone", "fullHeart", "emptyHeart"};

	ResourcesManager::LoadTextureAtlas("textureAtlas", "resources/textures/mushroom.png", names, 16, 16);

	glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(window_size.x), 0.f, static_cast<float>(window_size.y), -100.f, 100.f);
	ResourcesManager::GetShaderProgram("spriteShader")->Use();
	ResourcesManager::GetShaderProgram("spriteShader")->SetIn("tex", 0);
	ResourcesManager::GetShaderProgram("spriteShader")->SetMatrix4("projectionMat", projectionMatrix);
}
