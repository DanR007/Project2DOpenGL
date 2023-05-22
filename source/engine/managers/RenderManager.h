#pragma once
#include "../renderer/AnimSprite.h"

#include "ResourcesManager.h"

#include "MemoryManager.h"
#include "MemoryManager.h"

#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

class RenderManager
{
public:
	RenderManager() {}
	~RenderManager();

	template<typename T>
	T* CreateSprite(Actor* owner, const glm::vec2& position, const glm::vec2& size, const std::string& initSpriteName, const float& rotation = 0.f)
	{
		std::map<std::string, Renderer::RenderImage*>::const_iterator it = _all_images.find(initSpriteName);


		if (it == _all_images.end())
		{
			std::cout << "Can't find image with this init sprite name: " + initSpriteName << std::endl;
			std::cout << "Create new" << std::endl;

			CreateNewImage(ResourcesManager::GetTexture("textureAtlas"), ResourcesManager::GetShaderProgram("spriteShader"), initSpriteName);
		}

		it = _all_images.find(initSpriteName);

		std::shared_ptr<T> new_sprite = std::make_shared<T>(it->second, owner, position, size, rotation);
		_all_sprites[it->second].push_back(new_sprite.get());
		GetEngine()->GetMemoryManager()->AddObject(new_sprite);

		return new_sprite.get();
	}

	Renderer::RenderImage* CreateNewImage(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr <Renderer::ShaderProgram> shader, const std::string& initialSubtextureName);

	void Update(const float& deltaTime);

	void Erase(Renderer::Sprite* spr);
private:
	void GetSpritesInView(std::vector<Renderer::Sprite*>& in_view, Renderer::RenderImage* img);
	void ClearBuffer();
	size_t GetCount(Renderer::RenderImage* img);
	void Draw(Renderer::RenderImage* img);

	GLuint _buffer_matrix;

	std::map<std::string, Renderer::RenderImage*> _all_images;
	std::map<Renderer::RenderImage*, std::vector<Renderer::Sprite*>> _all_sprites;
};