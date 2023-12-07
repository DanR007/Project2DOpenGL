#pragma once
#include "../renderer/AnimSprite.h"

#include "ResourcesManager.h"
#include "EngineManager.h"
#include "MemoryManager.h"

#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>


#define MAP_CELL 0
#define STATIC 1
#define DYNAMIC 2
#define BACKGROUND 3
#define BUTTON 4
#define TEXT_IMAGES 5


template< typename T >
class pointer_comparator
{
public :
    bool operator()( T x, T y ) const 
	{ 
		if((x->GetRenderLayer()) == (y->GetRenderLayer()))
			return x->GetSpriteName() < y->GetSpriteName();
		else
			return (*x) < (*y);
	}
};

class RenderManager
{
public:
	RenderManager() 
	{
		glGenBuffers(1, &_buffer_matrix);
	}
	~RenderManager();

	/*render_layer for static game actors is STATIC, for dynamic DYNAMIC, for UI background is BACKGROUND, for button use BUTTON and for text and images TEXT_IMAGES*/
	template<typename T>
	T* CreateSprite(Object* owner, const glm::vec2& position, const glm::vec2& size, const std::string& initSpriteName, 
		const std::string& texture_atlas_name = "textureAtlas", const uint8_t& render_layer = STATIC, const float& rotation = 0.f)
	{
		std::map<std::string, Renderer::RenderImage*>::const_iterator it = _map_all_images.find(initSpriteName);


		if (it == _map_all_images.end())
		{
			std::cout << "Can't find image with this init sprite name: " + initSpriteName << std::endl;
			std::cout << "Create new image with sprite: " + initSpriteName << std::endl;
			Renderer::RenderImage* img = CreateNewImage(GetEngine()->GetResourcesManager()->GetTexture(texture_atlas_name),
				GetEngine()->GetResourcesManager()->GetShaderProgram("spriteShader"), initSpriteName, render_layer);

			it = _map_all_images.find(initSpriteName);
		}
		
		T* new_sprite = new T(it->second, owner, position, size, rotation);
		_all_sprites[it->second].push_back(new_sprite);

		return new_sprite;
	}
	/*render_layer for static game actors is STATIC, for dynamic DYNAMIC, for UI background is BACKGROUND, for button use BUTTON and for text and images TEXT_IMAGES*/
	template<typename T>
	T* CreateSprite(Object* owner, const glm::vec2& position, const glm::vec2& size
	, const std::string& initSpriteName, const uint8_t& render_layer = STATIC, const float& rotation = 0.f)
	{
		return CreateSprite<T>(owner, position, size, initSpriteName, "textureAtlas", render_layer, rotation);
	}
	/// @brief создание новой картинки (не UI)
	/// @param texture текстура которая будет использоваться
	/// @param shader шейдер
	/// @param initialSubtextureName имя подтекстуры для картинки
	/// @param render_layer слой рендера (0 - самый первый)
	/// @return сама картинка
	Renderer::RenderImage* CreateNewImage(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr <Renderer::ShaderProgram> shader,
		const std::string& initialSubtextureName, const uint8_t& render_layer);

	void Update(const float& deltaTime);

	void Erase(Renderer::Sprite* spr);
private:
	/// @brief заполняем массив видимыми в пределах экрана, и подлежащих отрисовки, спрайтами
	/// @param in_view массив нужных для рендера спрайтов
	/// @param img картинка на которой основаны эти спрайты
	void GetSpritesInView(std::vector<Renderer::Sprite*>& in_view, Renderer::RenderImage* img);
	/// @brief очистка буффера матриц
	void ClearBuffer();
	/// @brief отрисовка спрайтов основанных на текстуре (Image)
	/// @param img текстура на которой основаны все спрайты, которые сейчас обрабатываются
	void Draw(Renderer::RenderImage* img);

	GLuint _buffer_matrix;
	/// @brief словарь всех имён созданных текстур
	std::map<std::string, Renderer::RenderImage*> _map_all_images;
	/// @brief словарь хранящий в порядке убывания по важности рендера (от 0 до N) текстур которые являются ключом к спрайтам
	std::map<Renderer::RenderImage*, std::vector<Renderer::Sprite*>, pointer_comparator<Renderer::RenderImage*>> _all_sprites;
};