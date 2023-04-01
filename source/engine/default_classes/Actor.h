#pragma once

#include <string>
#include <vector>
#include <memory>

#include <glm/vec2.hpp>

namespace Renderer
{
	class AnimSprite;
	class Texture2D;
	class ShaderProgram;
}
namespace Physics
{
	class Collider;
}

namespace Game
{
	class Actor
	{
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="texture">Texture which we will draw</param>
		/// <param name="shader">Shader which processes drawing</param>
		/// <param name="initSubtextureName">Subtexture name of animation sprite</param>
		/// <param name="startPosition">Position of actor. </param>
		/// <param name="startSize">Size of actor, collider, sprite</param>
		/// <param name="startRotation">Rotation of actor, collider, sprite</param>
		Actor(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader,
			const std::string& initSubtextureName,
			const glm::vec2& startPosition/*lower left point*/, const glm::vec2& startSize = glm::vec2(1.f), const float startRotation = 0.f);
		Actor(Actor&& a) noexcept;

		Actor() = delete;
		~Actor();

		virtual void Update(float deltaTime);
		virtual void BeginPlay();

		inline std::shared_ptr<Renderer::AnimSprite> GetAnimSprite();
		inline std::shared_ptr<Physics::Collider> GetCollider() const  { return _collider; }
		inline glm::vec2 GetPosition() const { return _world_position; }
		inline glm::vec2 GetRelativePosition() const { return _relative_position; }
		inline float GetRotation() const { return _rotation; }

		void SetPosition(const glm::vec2& new_position);
		void SetSize(const glm::vec2& new_size);
		void SetRotation(const float& new_rotation);
		void SetRelativePosition(const glm::vec2& new_position);

		void SetIterator(std::vector<std::shared_ptr<Game::Actor>>::iterator iterator) { _iterator = iterator; }
		void SetCollider(std::shared_ptr<Physics::Collider> collider) { _collider = collider; }

		void AddWorldPosition(const glm::vec2& d_pos);
		void AddWorldRotation(const float& d_rot);

		void AddAnimState(const std::string& stateName, std::vector<std::pair<std::string, float>> subTextureDuration);
		void PlayAnim(const std::string& stateName);

		void DestroyActor();

	protected:
		glm::vec2 _world_position, _relative_position;
		glm::vec2 _size;
		float _rotation;

		std::vector<std::shared_ptr<Game::Actor>>::iterator _iterator;

		std::unique_ptr<Renderer::AnimSprite> _anim_sprite;
		std::shared_ptr<Physics::Collider> _collider;
	};
}