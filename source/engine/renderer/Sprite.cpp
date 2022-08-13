#include "Sprite.h"

#include "TextureRender.h"
#include "ShaderRender.h"

#include <glm/matrix.hpp>
namespace Renderer
{
	Sprite::Sprite(std::shared_ptr<Texture2D> texture, std::shared_ptr<ShaderProgram> shader, 
		const std::string& initialSubtextureName, const glm::vec2& position, 
		const glm::vec2& size, const float rotation)
		: spr_texture(texture), spr_shader(shader), spr_pos(position),
		spr_rot(rotation), spr_size(size), spr_subtexture_name(initialSubtextureName)
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
		GLfloat texCoord[] =
		{
				subTexture.left_bottom_UV.x, subTexture.left_bottom_UV.y,
				subTexture.left_bottom_UV.x, subTexture.right_upper_UV.y,
				subTexture.right_upper_UV.x, subTexture.left_bottom_UV.y,
				subTexture.right_upper_UV.x, subTexture.right_upper_UV.y
		};

		glGenVertexArrays(1, &spr_vertex_array_objects);

		glGenBuffers(1, &texture_coord_buffer);
		glGenBuffers(1, &vertex_coord_buffer);
		glGenBuffers(1, &vertex_element_buffer);

		glBindVertexArray(spr_vertex_array_objects);

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
		glDeleteVertexArrays(1, &spr_vertex_array_objects);
	}

	void Sprite::SetPosition(const glm::vec2& newPosition)
	{
		spr_pos = newPosition;
	}
	void Sprite::SetSize(const glm::vec2& newSize)
	{
		spr_size = newSize;
	}
	void Sprite::SetRotation(const float newRotation)
	{
		spr_rot = newRotation;
	}

	void Sprite::Render() const
	{
		spr_shader->Use();

		glm::mat4 model(1.f);//create a model matrix
		
		model = glm::translate(model, glm::vec3(spr_pos, 0.f));
		model = glm::translate(model, glm::vec3(0.5f * spr_size.x, 0.5f * spr_size.y, 0.f));
		model = glm::rotate(model, glm::radians(spr_rot), glm::vec3(0.f, 0.f, 1.f));
		model = glm::translate(model, glm::vec3(-0.5f * spr_size.x, -0.5f * spr_size.y, 0.f));
		model = glm::scale(model, glm::vec3(spr_size, 1.f));

		glBindVertexArray(spr_vertex_array_objects);
		spr_shader->SetMatrix4("modelMat", model);

		glActiveTexture(GL_TEXTURE0);
		spr_texture->Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}


}

