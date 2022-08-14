#include "main.h"
#include "engine/managers/ResourcesManager.h"
#include "engine/managers/PhysicsManager.h"

#include "engine/renderer/ShaderRender.h"
#include "engine/renderer/TextureRender.h"
#include "engine/renderer/AnimSprite.h"

#include "game/Actor.h"
#include "game/Pawn.h"
#include "game/MainCharacter.h"

#include "game/gameobjects/WallActor.h"

#include <iostream>
#include <time.h>
#include <chrono>

std::vector<Game::Pawn*> pawns;
std::shared_ptr<Game::MainCharacter> main_character;
std::vector<std::shared_ptr<Game::Actor>> all_actors;

void glfwWindowSizeCallback(GLFWwindow* currentWindow, int size_x, int size_y)
{
	window_size.x = size_x;
	window_size.y = size_y;
	glViewport(0, 0, window_size.x, window_size.y);
}

void glfwKeyCallback(GLFWwindow* currentWindow, int key, int scancode, int action, int mode)
{
	switch(action)
	{
		case GLFW_PRESS:
			switch (key)
			{
			case GLFW_KEY_ESCAPE:
					glfwSetWindowShouldClose(currentWindow, GLFW_TRUE);
					break;
			case GLFW_KEY_W:
				main_character->ChangeMoveVector(up_vector);
				break;
			case GLFW_KEY_S:
				main_character->ChangeMoveVector(up_vector * -1.f);
				break;
			case GLFW_KEY_D:
				main_character->ChangeMoveVector(right_vector);
				break;
			case GLFW_KEY_A:
				main_character->ChangeMoveVector(right_vector * -1.f);
				break;
			}
		break;
		case GLFW_RELEASE:
			switch (key)
			{
			case GLFW_KEY_W:
				main_character->ChangeMoveVector(up_vector * -1.f);
				break;
			case GLFW_KEY_S:
				main_character->ChangeMoveVector(up_vector);
				break;
			case GLFW_KEY_D:
				main_character->ChangeMoveVector(right_vector * -1.f);
				break;
			case GLFW_KEY_A:
				main_character->ChangeMoveVector(right_vector);
				break;
			}
			break;
		case GLFW_REPEAT:
				/*if (key == GLFW_KEY_W)
					pawns[0]->Move(up_vector);

				if (key == GLFW_KEY_S)
					pawns[0]->Move(up_vector * -1.f);

				if (key == GLFW_KEY_D)
					pawns[0]->Move(right_vector);

				if (key == GLFW_KEY_A)
					pawns[0]->Move(right_vector * -1.f);*/
			break;
	}
}

int main(int argc, char** argv)
{
	GLFWwindow* window;
	
	if (!glfwInit())
	{
		std::cerr << "GLFW does not work correct or cant open idk" << std::endl;
		return -1;
	}
	{
		ResourcesManager manager = ResourcesManager(*argv);

		window = glfwCreateWindow(window_size.x, window_size.y, "Platformer2D", NULL, NULL);

		if (!window)
		{
			std::cerr << "Cant create a window" << std::endl;
			glfwTerminate();
			return -1;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);
		glfwSetKeyCallback(window, glfwKeyCallback);

		glfwMakeContextCurrent(window);

		if (!gladLoadGL())
		{
			std::cerr << "GLAD does not exist or cant open" << std::endl;
			return -1;
		}

		//std::shared_ptr<Renderer::ShaderProgram> defShader = manager.LoadShaderPrograms("default", DEFAULT_FRAGMENT_SHADER_PATH, DEFAULT_VERTEX__SHADER_PATH);
		std::shared_ptr<Renderer::ShaderProgram> textureShader = manager.LoadShaderPrograms("texture", TEXTURE_FRAGMENT_SHADER_PATH, TEXTURE_VERTEX_SHADER_PATH);
		auto sh = manager.LoadShaderPrograms("spriteShader", SPRITE_FRAGMENT_SHADER_PATH, SPRITE_VERTEX_SHADER_PATH);
		//std::shared_ptr<Renderer::Texture2D> texture = manager.LoadTexture("mushroom", "resources/textures/mushroom.png");
		
		/*GLuint coordinateVertexBufferObjects, textureVertexBufferObjects, vertexArrayObjects;
		glGenVertexArrays(1, &vertexArrayObjects);
		glGenBuffers(1, &coordinateVertexBufferObjects);
		glGenBuffers(1, &textureVertexBufferObjects);

		glBindVertexArray(vertexArrayObjects);

		glBindBuffer(GL_ARRAY_BUFFER, coordinateVertexBufferObjects);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_coord), triangle_coord, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


		glBindBuffer(GL_ARRAY_BUFFER, textureVertexBufferObjects);
		glBufferData(GL_ARRAY_BUFFER, sizeof(texture_coordinates), texture_coordinates, GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		//glEnableVertexAttribArray(1);
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);

		glBindVertexArray(0);*/

		glClearColor(1.f, 1.f, 1.f, 1.f);

		std::vector<std::string> names = { "mush1", "mush2", "mush3", "wall"};
		
		manager.LoadTextureAtlas("textureAtlas", "resources/textures/mushroom.png", names, 16, 16);
		
		//mushroom - texture name
		//names - vector of names subtextures
		glm::vec2 mainCharacterSize = glm::ivec2(100, 100);
		main_character = std::make_shared<Game::MainCharacter>(std::move(manager.LoadAnimSprite("animSprite", "textureAtlas", "spriteShader", mainCharacterSize.x, mainCharacterSize.y, std::string("mush1"))), 100.f,
			glm::vec2(window_size.x / 2 - mainCharacterSize.x / 2, window_size.y / 2 - mainCharacterSize.y / 2), mainCharacterSize);

		glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(window_size.x), 0.f, static_cast<float>(window_size.y), -100.f, 100.f);
		manager.GetShaderProgram("spriteShader")->Use();
		manager.GetShaderProgram("spriteShader")->SetIn("tex", 0);
		manager.GetShaderProgram("spriteShader")->SetMatrix4("projectionMat", projectionMatrix);

		std::vector<std::pair<std::string, float>> stateDuration =
		{
			std::make_pair(std::string("mush1"), 1.f),
			std::make_pair(std::string("mush2"), 1.f),
			std::make_pair(std::string("mush3"), 1.f)
		};

		main_character->GetAnimSprite()->InsertState("walk", stateDuration);
		main_character->GetAnimSprite()->SetState("walk");

		//all_actors.push_back(std::make_shared<Game::Actor>(nullptr, glm::vec2(0.f, 0.f), window_size, 0.f));
		all_actors.push_back(std::make_shared<Game::Actor>(manager.GetTexture("textureAtlas"), manager.GetShaderProgram("spriteShader"), "wall", glm::vec2(800.f, 360.f), glm::vec2(240, 240)));
		all_actors.push_back(std::make_shared<Game::Actor>(manager.LoadAnimSprite("wallSprite", "textureAtlas", "spriteShader", 40, 40, std::string("wall")), glm::vec2(500.f, 360.f), glm::vec2(40, 40)));
		all_actors.push_back(std::make_shared<Game::Actor>(manager.GetTexture("textureAtlas"), manager.GetShaderProgram("spriteShader"), "wall", glm::vec2(800.f, 600.f), glm::vec2(240, 240)));
		auto lastTime = std::chrono::high_resolution_clock::now();

		while (!glfwWindowShouldClose(window))
		{
			glClear(GL_COLOR_BUFFER_BIT);

			auto currentTime = std::chrono::high_resolution_clock::now();
			float duration = float(double(std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count()) / 1e9);
			lastTime = currentTime;

			main_character->Update(duration);
			for (std::shared_ptr<Game::Actor> actor : all_actors)
			{
				actor->Update(duration);
				//glBindTexture(GL_TEXTURE_2D, 0);
			}
			//pawn->GetAnimSprite()->SetPosition(pawn->GetAnimSprite()->GetPosition() + glm::vec2(duration, 0));
			//texture->Bind();
			/*GLint uniform = glGetUniformLocation(shaderProgram->GetID(), "vertexColor");
			glUniform4f(uniform, 1.f, -0.5f, 0.5f, 1.f);
			GLint uniformPos = glGetUniformLocation(shaderProgram->GetID(), "pos");
			f = sin(glfwGetTime()) / 2 + 0.5f;
			glUniform1f(uniformPos, f);
			*/

			/*glUniform1i(glGetUniformLocation(textureShader->GetID(), "textureS"), 0);
			glBindVertexArray(vertexArrayObjects);

			glDrawArrays(GL_TRIANGLES, 0, 6);

			

			glBindVertexArray(0);
			*/
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	return 0;
}