#pragma once

#include <string>
#include <memory>
#include <map>
#include <vector>

namespace Renderer
{
	class ShaderProgram;
	class Texture2D;
	class Sprite;
	class AnimSprite;
}

class ResourcesManager
{
public:
	ResourcesManager(const std::string& executablePath);

	std::shared_ptr<Renderer::ShaderProgram> LoadShaderPrograms(const std::string& shaderName, const std::string& fragmentPath, const std::string& vertexPath);
	std::shared_ptr<Renderer::ShaderProgram> GetShaderProgram(const std::string& shaderName) const;

	std::shared_ptr<Renderer::Texture2D> LoadTexture(const std::string& textureName, const std::string& texturePath);
	std::shared_ptr<Renderer::Texture2D> GetTexture(const std::string& textureName) const;
	std::shared_ptr<Renderer::Texture2D> LoadTextureAtlas(const std::string& textureName, const std::string& texturePath,
		const std::vector<std::string>& subTextureNamesArr,
		const unsigned int width, const unsigned int height);

	std::shared_ptr<Renderer::Sprite> LoadSprite(const std::string& spriteName,
		const std::string& textureName,
		const std::string& shaderName,
		const unsigned int spriteWidth,
		const unsigned int spriteHeight,
		std::string& subTextureName);
	std::shared_ptr<Renderer::Sprite> GetSprite(const std::string& spriteName) const;

	std::shared_ptr<Renderer::AnimSprite> ResourcesManager::LoadAnimSprite(const std::string& spriteName,
		const std::string& textureName,
		const std::string& shaderName,
		const unsigned int spriteWidth,
		const unsigned int spriteHeight,
		std::string& subTextureName);
	std::shared_ptr<Renderer::AnimSprite> GetAnimSprite(const std::string& animSpriteName) const;
	
private:
	std::string ReadShaderProgramFile(const std::string& path);
	std::string exe_path;

	typedef std::map<std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramMap;
	ShaderProgramMap shader_program_map;

	typedef std::map <std::string, std::shared_ptr<Renderer::Texture2D>> TexturesMap;
	TexturesMap textures_map;

	typedef std::map<std::string, std::shared_ptr<Renderer::Sprite>> SpritesMap;
	SpritesMap sprites_map;

	typedef std::map<std::string, std::shared_ptr<Renderer::AnimSprite>> AnimSpritesMap;
	AnimSpritesMap anim_sprites_map;
};