#include "main.h"
#include "engine/managers/ResourcesManager.h"

#include "engine/renderer/ShaderRender.h"
#include "engine/renderer/TextureRender.h"
#include "engine/renderer/AnimSprite.h"

#include "game/Actor.h"
#include "game/Pawn.h"

#include <iostream>
#include <time.h>
#include <chrono>

std::vector<Game::MainCharacter*> pawns;

void glfwWindowSizeCallback(GLFWwindow* currentWindow, int size_x, int size_y)
{
	window_size.x = size_x;
	window_size.y = size_y;
	glViewport(0, 0, window_size.x, window_size.y);
}

void glfwKeyCallback(GLFWwindow* currentWindow, int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(currentWindow, GLFW_TRUE);
			break;
		case GLFW_KEY_W:
			std::cout << "Press W" << std::endl;
			pawns[0]->Move(glm::vec2(0.f, 1.f));
			break;
		case GLFW_KEY_S:
			std::cout << "Press s" << std::endl;
			pawns[0]->Move(glm::vec2(0.f, -1.f));
			break;
		case GLFW_KEY_D:
			std::cout << "Press d" << std::endl;
			pawns[0]->Move(glm::vec2(1.f, 0.f));
			break;
		case GLFW_KEY_A:
			std::cout << "Press a" << std::endl;
			pawns[0]->Move(glm::vec2(-1.f, 0.f));
			break;
		}
		
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

		glClearColor(0.f, 0.f, 0.f, 1.f);

		std::string s = "m4";
		std::vector<std::string> names = { "m1", "m2", "m3", s};
		
		manager.LoadTextureAtlas("mushroom", "resources/textures/mushroom.png", names, 16, 16);
		
		//mushroom - texture name
		//names - vector of names subtextures
		pawns.push_back(new Game::MainCharacter(std::move(manager.LoadAnimSprite("animSprite", "mushroom", "spriteShader", 261, 261, std::string("m1"))), 100.f, glm::vec2(0.f, 0.f), glm::vec2(261, 261)));

		glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(window_size.x), 0.f, static_cast<float>(window_size.y), -100.f, 100.f);
		manager.GetShaderProgram("spriteShader")->Use();
		manager.GetShaderProgram("spriteShader")->SetIn("tex", 0);
		manager.GetShaderProgram("spriteShader")->SetMatrix4("projectionMat", projectionMatrix);

		std::vector<std::pair<std::string, float>> stateDuration =
		{
			std::make_pair(std::string("m1"), 1.f),
			std::make_pair(std::string("m2"), 1.f),
			std::make_pair(std::string("m3"), 1.f)
		};



		pawns[0]->GetAnimSprite()->InsertState("walk", stateDuration);

		auto lastTime = std::chrono::high_resolution_clock::now();

		pawns[0]->GetAnimSprite()->SetState("walk");


		while (!glfwWindowShouldClose(window))
		{
			glClear(GL_COLOR_BUFFER_BIT);

			auto currentTime = std::chrono::high_resolution_clock::now();
			float duration = float(double(std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count()) / 1e9);
			lastTime = currentTime;

			pawns[0]->Update(duration);

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