#pragma once

#include "../../main.h"

#include <string>
#include <memory>
#include <map>
#include <vector>

#define DEFAULT_VERTEX__SHADER_PATH "resources/shaders/defVertexShader.txt"
#define DEFAULT_FRAGMENT_SHADER_PATH "resources/shaders/defFragmentShader.txt"
#define TEXTURE_VERTEX_SHADER_PATH "resources/shaders/textureVertexShader.txt"
#define TEXTURE_FRAGMENT_SHADER_PATH "resources/shaders/textureFragmentShader.txt"
#define SPRITE_VERTEX_SHADER_PATH "resources/shaders/spriteVertexShader.txt"
#define SPRITE_FRAGMENT_SHADER_PATH "resources/shaders/spriteFragmentShader.txt"

namespace Renderer
{
	class ShaderProgram;
	class Texture2D;
	class Sprite;
	class AnimSprite;
}


class Actor;


typedef std::map<std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramMap;
typedef std::map <std::string, std::shared_ptr<Renderer::Texture2D>> TexturesMap;
typedef std::map <std::string, std::shared_ptr<Renderer::Sprite>> SpritesMap;
typedef std::map <std::string, std::shared_ptr<Renderer::AnimSprite>> AnimSpritesMap;

class ResourcesManager
{
public:
	static std::shared_ptr<Renderer::ShaderProgram> LoadShaderPrograms(const std::string& shaderName, const std::string& fragmentPath, const std::string& vertexPath);
	static std::shared_ptr<Renderer::ShaderProgram> GetShaderProgram(const std::string& shaderName);

	static std::shared_ptr<Renderer::Texture2D> LoadTexture(const std::string& textureName, const std::string& texturePath);
	static std::shared_ptr<Renderer::Texture2D> GetTexture(const std::string& textureName);
	static std::shared_ptr<Renderer::Texture2D> LoadTextureAtlas(const std::string& textureName, const std::string& texturePath,
		const std::vector<std::string>& subTextureNamesArr,
		const unsigned int width, const unsigned int height);

	static std::shared_ptr<Renderer::Sprite> LoadSprite(const std::string& spriteName,
		const std::string& textureName,
		const std::string& shaderName,
		const unsigned int spriteWidth,
		const unsigned int spriteHeight,
		const std::string& subTextureName);
	static std::shared_ptr<Renderer::Sprite> GetSprite(const std::string& spriteName);

	static std::shared_ptr<Renderer::AnimSprite> ResourcesManager::LoadAnimSprite(const std::string& spriteName,
		const std::string& textureName,
		const std::string& shaderName,
		const unsigned int spriteWidth,
		const unsigned int spriteHeight,
		const std::string& subTextureName);
	static std::shared_ptr<Renderer::AnimSprite> GetAnimSprite(const std::string& animSpriteName);
	
	static void LoadAll(const std::string& executablePath);
private:
	static std::string ReadShaderProgramFile(const std::string& path);
	static std::string exe_path;

	static ShaderProgramMap shader_program_map;
	static TexturesMap textures_map;
	static SpritesMap sprites_map;
	static AnimSpritesMap anim_sprites_map;
};

//ShaderProgramMap ResourcesManager::shader_program_map;
//TexturesMap ResourcesManager::textures_map;
//SpritesMap ResourcesManager::sprites_map;
//AnimSpritesMap ResourcesManager::anim_sprites_map;