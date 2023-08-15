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
#define NEW_SPRITE_FRAGMENT_SHADER_PATH "resources/shaders/newSpriteFragmentShader.txt"

namespace Renderer
{
	class ShaderProgram;
	class Texture2D;
}


class Actor;


typedef std::map<std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramMap;
typedef std::map <std::string, std::shared_ptr<Renderer::Texture2D>> TexturesMap;

class ResourcesManager
{
public:
	ResourcesManager()
	{

	}
	~ResourcesManager();
	 std::shared_ptr<Renderer::ShaderProgram> LoadShaderPrograms(const std::string& shaderName, const std::string& fragmentPath, const std::string& vertexPath);
	 std::shared_ptr<Renderer::ShaderProgram> GetShaderProgram(const std::string& shaderName);

	 std::shared_ptr<Renderer::Texture2D> LoadTexture(const std::string& textureName, const std::string& texturePath);
	 std::shared_ptr<Renderer::Texture2D> GetTexture(const std::string& textureName);
	 std::shared_ptr<Renderer::Texture2D> LoadTextureAtlas(const std::string& textureName, const std::string& texturePath,
		const std::vector<std::string>& subTextureNamesArr,
		 const std::vector<uint8_t>& subTextureSizeArr);
	
	 void LoadAll(const std::string& executablePath);

private:
	 std::string ReadShaderProgramFile(const std::string& path);
	 std::string exe_path;

	 ShaderProgramMap shader_program_map;
	 TexturesMap textures_map;
};