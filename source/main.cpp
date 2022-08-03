#include "main.h"
#include "managers/ResourcesManager.h"

#include "renderer/ShaderRender.h"
#include "renderer/TextureRender.h"

#include <iostream>

#define DEFAULT_VERTEX__SHADER_PATH "resources/shaders/defVertexShader.txt"
#define DEFAULT_FRAGMENT_SHADER_PATH "resources/shaders/defFragmentShader.txt"
#define TEXTURE_VERTEX_SHADER_PATH "resources/shaders/textureVertexShader.txt"
#define TEXTURE_FRAGMENT_SHADER_PATH "resources/shaders/textureFragmentShader.txt"

void glfwWindowSizeCallback(GLFWwindow* currentWindow, int size_x, int size_y)
{
	window_size.x = size_x;
	window_size.y = size_y;
	glViewport(0, 0, window_size.x, window_size.y);
}

void glfwKeyCallback(GLFWwindow* currentWindow, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(currentWindow, GLFW_TRUE);
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
		ResourcesManager manager(*argv);

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

		std::shared_ptr<Renderer::Texture2D> texture = manager.LoadTexture("mushroom", "resources/textures/mushroom.png");

		GLuint coordinateVertexBufferObjects, textureVertexBufferObjects, vertexArrayObjects;
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

		glBindVertexArray(0);

		glClearColor(1.f, 1.f, 1.f, 0.f);

		while (!glfwWindowShouldClose(window))
		{
			glClear(GL_COLOR_BUFFER_BIT);

			textureShader->Use();
			texture->Bind();
			/*GLint uniform = glGetUniformLocation(shaderProgram->GetID(), "vertexColor");
			glUniform4f(uniform, 1.f, -0.5f, 0.5f, 1.f);
			GLint uniformPos = glGetUniformLocation(shaderProgram->GetID(), "pos");
			f = sin(glfwGetTime()) / 2 + 0.5f;
			glUniform1f(uniformPos, f);
			*/
			glUniform1i(glGetUniformLocation(textureShader->GetID(), "textureS"), 0);
			glBindVertexArray(vertexArrayObjects);

			glDrawArrays(GL_TRIANGLES, 0, 6);



			glBindVertexArray(0);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	return 0;
}