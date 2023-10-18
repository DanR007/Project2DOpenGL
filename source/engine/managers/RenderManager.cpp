#include "RenderManager.h"

#include "EngineManager.h"

#include "../renderer/TextureRender.h"
#include "../renderer/ShaderRender.h"

#include <algorithm>

RenderManager::~RenderManager()
{
	//clear all dynamic memoru which we add to images
	auto it = _map_all_images.begin();
	for (; it != _map_all_images.end(); )
	{
		_all_sprites[it->second].clear();

		delete it->second;
		it = _map_all_images.erase(it);
	}

	ClearBuffer();
}

Renderer::RenderImage* RenderManager::CreateNewImage(std::shared_ptr<Renderer::Texture2D> texture,
	std::shared_ptr<Renderer::ShaderProgram> shader, const std::string& initialSubtextureName, const uint8_t& render_layer)
{
	Renderer::RenderImage* img = new Renderer::RenderImage(texture, shader, initialSubtextureName, render_layer);
	_map_all_images.emplace(std::make_pair(initialSubtextureName, img)).first->second;
	
	return img;
}

void RenderManager::Update(const float& deltaTime)
{
	for (auto it = _all_sprites.begin(); it != _all_sprites.end(); ++it)
	{	
		(it->first)->GetShader()->Use();
		(it->first)->GetShader()->SetUInt("diffuse_layer", (it->first)->GetDiffuseLayer());
		(it->first)->GetTexture()->Bind();

		Draw(it->first);
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
	size_t count = _sprites.size();
	matrixes = new glm::mat4[count];

	for (int i = 0; i < count; i++)
	{
		glm::mat4 matrix(1.f);

		glm::vec2 position = _sprites[i]->GetPosition();
		glm::vec2 size = _sprites[i]->GetSize();

		matrix = glm::translate(matrix, glm::vec3(position, 0.f));
		matrix = glm::translate(matrix, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.f));
		matrix = glm::rotate(matrix, glm::radians(_sprites[i]->GetRotation()), glm::vec3(0.f, 0.f, 1.f));
		matrix = glm::translate(matrix, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.f));
		matrix = glm::scale(matrix, glm::vec3(size, 1.f));

		matrixes[i] = matrix;
	}

	glBindBuffer(GL_ARRAY_BUFFER, _buffer_matrix);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(glm::mat4), &matrixes[0], GL_DYNAMIC_DRAW);

	for (int i = 0; i < count; i++)
	{
		glBindVertexArray(_sprites[i]->GetRenderImage()->GetVAO());
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
	
	for (int i = 0; i < count; i++)
	{
		glBindVertexArray(_sprites[i]->GetRenderImage()->GetVAO());
		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, count);
		glBindVertexArray(0);
	}

	delete[] matrixes;
	matrixes = nullptr;

	_sprites.clear();

	glActiveTexture(GL_TEXTURE0);
}

void RenderManager::GetSpritesInView(std::vector<Renderer::Sprite*>& in_view, Renderer::RenderImage* img)
{
	size_t size = _all_sprites[img].size();
	for (size_t i = 0; i < size; i++)
	{
		if (_all_sprites[img][i])
		{
			if(_all_sprites[img][i]->GetNeedToRender())
			{
				in_view.push_back(_all_sprites[img][i]);
			}
			else
			{
#ifdef DEBUG_RENDER
			std::cout << "Sprite doesnt need to render" << std::endl;
#endif //DEBUG_RENDER
			}
		}
		else
		{
#ifdef DEBUG_RENDER
			std::cout << "Sprite is nullptr in GetSpritesInView" << std::endl;
#endif //DEBUG_RENDER
		}
	}
}

void RenderManager::ClearBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
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
