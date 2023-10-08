#pragma once
#include "../renderer/AnimSprite.h"

#include "ResourcesManager.h"
#include "EngineManager.h"
#include "MemoryManager.h"

#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

class RenderManager
{
public:
	RenderManager() 
	{
		glGenBuffers(1, &_buffer_matrix);
	}
	~RenderManager();

	/*render_layer for game actors is 0, for UI background is 1, for text and images 2*/
	template<typename T>
	T* CreateSprite(Actor* owner, const glm::vec2& position, const glm::vec2& size, const std::string& initSpriteName, 
		const std::string& texture_atlas_name = "textureAtlas", const uint8_t& layer = 0, const float& rotation = 0.f)
	{
		std::map<std::string, Renderer::RenderImage*>::const_iterator it = _map_all_images.find(initSpriteName);


		if (it == _map_all_images.end())
		{
			std::cout << "Can't find image with this init sprite name: " + initSpriteName << std::endl;
			std::cout << "Create new image with sprite: " + initSpriteName << std::endl;
			Renderer::RenderImage* img = CreateNewImage(GetEngine()->GetResourcesManager()->GetTexture(texture_atlas_name),
				GetEngine()->GetResourcesManager()->GetShaderProgram("spriteShader"), initSpriteName, layer);
			_all_images.push_back(img);
			SortImages();
		}

		it = _map_all_images.find(initSpriteName);

		T* new_sprite = new T(it->second, owner, position, size, rotation);
		_all_sprites[it->second].push_back(new_sprite);

		return new_sprite;
	}

	Renderer::RenderImage* CreateNewImage(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr <Renderer::ShaderProgram> shader,
		const std::string& initialSubtextureName, const uint8_t& render_layer);

	void Update(const float& deltaTime);

	void Erase(Renderer::Sprite* spr);
private:
	void SortImages();

	void GetSpritesInView(std::vector<Renderer::Sprite*>& in_view, Renderer::RenderImage* img);
	void ClearBuffer();
	size_t GetCount(Renderer::RenderImage* img);
	void Draw(Renderer::RenderImage* img);

	GLuint _buffer_matrix;
	std::vector<Renderer::RenderImage*> _all_images;

	std::map<std::string, Renderer::RenderImage*> _map_all_images;
	std::map<Renderer::RenderImage*, std::vector<Renderer::Sprite*>> _all_sprites;
};