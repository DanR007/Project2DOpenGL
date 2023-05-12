#include "Sprite.h"

#include "TextureRender.h"
#include "ShaderRender.h"

#include <glm/matrix.hpp>

#include "../../main.h"

namespace Renderer
{
	Sprite::Sprite(Renderer::RenderImage* image, Actor* owner, const glm::vec2& position, const glm::vec2& size, const float rotation)
		: MovableComponent(owner, position, size, rotation)
	{
		_image = image;
	}

	Sprite::~Sprite()
	{
#ifdef DEBUG
		std::cout << "Destroy Sprite" << std::endl;
#endif

	}

	void Sprite::SetNewSprite(const std::string& newSubtextureName)
	{
		_image->SetNewImage(newSubtextureName);
	}

	bool Sprite::InView() const
	{
		glm::vec2 view_position = glm::vec2(0);
		glm::vec2 sprite_end = _world_position + _size,
			view_size = view_position + glm::vec2(window_size);
		if (_world_position.x < view_position.x && sprite_end.x > view_position.x || _world_position.x >= view_position.x && _world_position.x < view_size.x)
		{
			return _world_position.y < view_position.y && sprite_end.y > view_position.y || _world_position.y >= view_position.y && _world_position.y < view_size.y;
		}
		else
		{
			return false;
		}
	}

	RenderImage::RenderImage(std::shared_ptr<Texture2D> texture, std::shared_ptr<ShaderProgram> shader, const std::string& initialSubtextureName):
		_texture(texture), _shader(shader), _subtexture_name(initialSubtextureName)
	{
		GLfloat vertex_buffer[] =
		{
			0.f, 0.f,//left bottom
			0.f, 1.f,//left top
			1.f, 0.f,//right bottom
			1.f, 1.f,//right top
		};

		GLuint element_buffer[] =
		{
			0, 1, 3,//first triangle
			0, 2, 3//second triangle
		};

		auto subTexture = texture->GetSubTexture(initialSubtextureName);
		//coordinates that will be use in sprite 
		//if > 1.f textures will repeat otherwise it will be crop
		GLfloat tex_buffer[] =
		{
				subTexture.left_bottom_UV.x, subTexture.left_bottom_UV.y,
				subTexture.left_bottom_UV.x, subTexture.right_upper_UV.y,
				subTexture.right_upper_UV.x, subTexture.left_bottom_UV.y,
				subTexture.right_upper_UV.x, subTexture.right_upper_UV.y
		};

		glGenVertexArrays(1, &_vertex_array_object);

		glGenBuffers(1, &_texture_buffer_object);
		glGenBuffers(1, &_vertex_buffer_object);
		glGenBuffers(1, &_element_buffer_object);

		glBindVertexArray(_vertex_array_object);

		glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_object);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer), vertex_buffer, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		glBindBuffer(GL_ARRAY_BUFFER, _texture_buffer_object);
		glBufferData(GL_ARRAY_BUFFER, sizeof(tex_buffer), tex_buffer, GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _element_buffer_object);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(element_buffer), element_buffer, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	RenderImage::~RenderImage()
	{
		glDeleteBuffers(1, &_vertex_buffer_object);
		glDeleteBuffers(1, &_texture_buffer_object);
		glDeleteBuffers(1, &_element_buffer_object);
		glDeleteVertexArrays(1, &_vertex_array_object);
	}

	void RenderImage::SetNewImage(const std::string& newSubtextureName)
	{
		auto subTexture = _texture->GetSubTexture(newSubtextureName);

		const GLfloat textureCoords[] =
		{
			subTexture.left_bottom_UV.x, subTexture.left_bottom_UV.y,
			subTexture.left_bottom_UV.x, subTexture.right_upper_UV.y,
			subTexture.right_upper_UV.x, subTexture.left_bottom_UV.y,
			subTexture.right_upper_UV.x, subTexture.right_upper_UV.y
		};

		glBindBuffer(GL_ARRAY_BUFFER, _texture_buffer_object);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(textureCoords), &textureCoords);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

