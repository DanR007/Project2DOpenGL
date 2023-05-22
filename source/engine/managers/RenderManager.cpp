#include "RenderManager.h"


#include "../renderer/TextureRender.h"
#include "../renderer/ShaderRender.h"

#include <algorithm>

RenderManager::~RenderManager()
{
	//clear all dynamic memoru which we add to images
	auto it = _all_images.begin();
	for (; it != _all_images.end(); )
	{
		_all_sprites[it->second].clear();
		delete it->second;
		it = _all_images.erase(it);
	}
}

Renderer::RenderImage* RenderManager::CreateNewImage(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader, const std::string& initialSubtextureName)
{
	return _all_images.emplace(std::make_pair(initialSubtextureName, new Renderer::RenderImage(texture, shader, initialSubtextureName))).first->second;
}

void RenderManager::Update(const float& deltaTime)
{
	for (auto it = _all_images.begin(); it != _all_images.end(); it++)
	{
		Draw(it->second);
	}
}

void RenderManager::Erase(Renderer::Sprite* spr)
{
	auto it = std::find(_all_sprites[spr->GetRenderImage()].begin(), _all_sprites[spr->GetRenderImage()].end(), spr);
	_all_sprites[spr->GetRenderImage()].erase(it);
}

void RenderManager::Draw(Renderer::RenderImage* img)
{
	glm::mat4* matrixes;

	std::vector<Renderer::Sprite*> _sprites;

	GetSpritesInView(_sprites, img);

	size_t count = _sprites.size(), count_sprite;
	count_sprite = count;

	matrixes = new glm::mat4[count];

	for (auto it = _sprites.begin(); it != _sprites.end(); it++)
	{
		if ((*it)->GetRenderImage() == img)
		{
			glm::mat4 matrix(1.f);

			glm::vec2 position = (*it)->GetPosition();
			glm::vec2 size = (*it)->GetSize();

			matrix = glm::translate(matrix, glm::vec3(position, 0.f));
			matrix = glm::translate(matrix, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.f));
			matrix = glm::rotate(matrix, glm::radians((*it)->GetRotation()), glm::vec3(0.f, 0.f, 1.f));
			matrix = glm::translate(matrix, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.f));
			matrix = glm::scale(matrix, glm::vec3(size, 1.f));

			matrixes[it - _sprites.begin()] = matrix;
		}
	}

	ClearBuffer();

	glGenBuffers(1, &_buffer_matrix);
	glBindBuffer(GL_ARRAY_BUFFER, _buffer_matrix);
	glBufferData(GL_ARRAY_BUFFER, count_sprite * sizeof(glm::mat4), &matrixes[0], GL_STATIC_DRAW);

	for (auto it = _sprites.begin(); it != _sprites.end(); it++)
	{
		glBindVertexArray((*it)->GetRenderImage()->GetVAO());
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4) * 4, (void*)0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4) * 4, (void*)(sizeof(glm::vec4)));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4) * 4, (void*)(2 * sizeof(glm::vec4)));
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4) * 4, (void*)(3 * sizeof(glm::vec4)));

		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);

		glBindVertexArray(0);
	}

	glActiveTexture(GL_TEXTURE0);

	img->GetShader()->Use();
	img->GetTexture()->Bind();

	for (auto it = _sprites.begin(); it != _sprites.end(); it++)
	{

		glBindVertexArray((*it)->GetRenderImage()->GetVAO());
		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, count_sprite);
		glBindVertexArray(0);
	}
	

	delete[] matrixes;
	matrixes = nullptr;
}

void RenderManager::GetSpritesInView(std::vector<Renderer::Sprite*>& in_view, Renderer::RenderImage* img)
{
	for (auto it = _all_sprites[img].begin(); it != _all_sprites[img].end(); it++)
	{
		if ((*it)->GetNeedToRender())
		{
			in_view.push_back((*it));
		}
	}
}

void RenderManager::ClearBuffer()
{
	glDeleteBuffers(1, &_buffer_matrix);
}

size_t RenderManager::GetCount(Renderer::RenderImage* img)
{
	size_t count = 0;
	
	for (auto it = _all_sprites[img].begin(); it != _all_sprites[img].end(); it++)
	{
		if ((*it)->GetNeedToRender())
		{
			count++;
		}
	}

	return count;
}
