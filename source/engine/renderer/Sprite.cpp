#include "Sprite.h"

#include "TextureRender.h"
#include "ShaderRender.h"

#include <glm/matrix.hpp>
namespace Renderer
{
	Sprite::Sprite(std::shared_ptr<Texture2D> texture, std::shared_ptr<ShaderProgram> shader, 
		const std::string& initialSubtextureName, Game::Actor* owner, const glm::vec2& position, 
		const glm::vec2& size, const float rotation)
		: MovableComponent(owner, position, size, rotation), _texture(texture), _shader(shader), _subtexture_name(initialSubtextureName)
	{
		GLfloat vertexCoord[] =
		{
			0.f, 0.f,//left bottom
			0.f, 1.f,//left top
			1.f, 0.f,//right bottom
			1.f, 1.f,//right top
		};

		GLuint elementArray[] =
		{
			0, 1, 3,//first triangle
			0, 2, 3//second triangle
		};

		auto subTexture = texture->GetSubTexture(initialSubtextureName);
		//coordinates that will be use in sprite 
		//if > 1.f textures will repeat otherwise it will be crop
		GLfloat texCoord[] =
		{
				subTexture.left_bottom_UV.x, subTexture.left_bottom_UV.y,
				subTexture.left_bottom_UV.x, subTexture.right_upper_UV.y,
				subTexture.right_upper_UV.x, subTexture.left_bottom_UV.y,
				subTexture.right_upper_UV.x, subTexture.right_upper_UV.y
		};

		glGenVertexArrays(1, &_vertex_array_objects);

		glGenBuffers(1, &texture_coord_buffer);
		glGenBuffers(1, &vertex_coord_buffer);
		glGenBuffers(1, &vertex_element_buffer);

		glBindVertexArray(_vertex_array_objects);

		glBindBuffer(GL_ARRAY_BUFFER, vertex_coord_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexCoord), vertexCoord, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		glBindBuffer(GL_ARRAY_BUFFER, texture_coord_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord), texCoord, GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertex_element_buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elementArray), elementArray, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	Sprite::~Sprite()
	{
		glDeleteBuffers(1, &vertex_coord_buffer);
		glDeleteBuffers(1, &texture_coord_buffer);
		glDeleteBuffers(1, &vertex_element_buffer);
		glDeleteVertexArrays(1, &_vertex_array_objects);
	}

	void Sprite::SetNewSprite(const std::string& newSubtextureName)
	{
		auto subTexture = _texture->GetSubTexture(newSubtextureName);

		const GLfloat textureCoords[] =
		{
			subTexture.left_bottom_UV.x, subTexture.left_bottom_UV.y,
			subTexture.left_bottom_UV.x, subTexture.right_upper_UV.y,
			subTexture.right_upper_UV.x, subTexture.left_bottom_UV.y,
			subTexture.right_upper_UV.x, subTexture.right_upper_UV.y
		};

		glBindBuffer(GL_ARRAY_BUFFER, texture_coord_buffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(textureCoords), &textureCoords);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Sprite::Render() const
	{
		_shader->Use();

		glm::mat4 model(1.f);//create a model matrix
		
		model = glm::translate(model, glm::vec3(_world_position, 0.f));
		model = glm::translate(model, glm::vec3(0.5f * _size.x, 0.5f * _size.y, 0.f));
		model = glm::rotate(model, glm::radians(_world_rotation), glm::vec3(0.f, 0.f, 1.f));
		model = glm::translate(model, glm::vec3(-0.5f * _size.x, -0.5f * _size.y, 0.f));
		model = glm::scale(model, glm::vec3(_size, 1.f));

		glBindVertexArray(_vertex_array_objects);
		_shader->SetMatrix4("modelMat", model);

		glActiveTexture(GL_TEXTURE0);
		_texture->Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}


}

