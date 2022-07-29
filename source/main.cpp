#include "main.h"
#include "managers/ResourcesManager.h"

#include "renderer/ShaderRender.h"

#include <iostream>

#define DEFAULT_VERTEX__SHADER_PATH "resources/shaders/defVertexShader.txt"
#define DEFAULT_FRAGMENT_SHADER_PATH "resources/shaders/defFragmentShader.txt"

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

	manager.LoadShaderPrograms("default", DEFAULT_FRAGMENT_SHADER_PATH, DEFAULT_VERTEX__SHADER_PATH);

	GLuint coordinateVertexBufferObjects, colorVertexBufferObjects, vertexArrayObjects, vertex2;
	glGenVertexArrays(1, &vertexArrayObjects);
	glGenBuffers(1, &coordinateVertexBufferObjects);
	glGenBuffers(1, &colorVertexBufferObjects);

	glBindVertexArray(vertexArrayObjects);

	glBindBuffer(GL_ARRAY_BUFFER, coordinateVertexBufferObjects);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_coord), triangle_coord, GL_STATIC_DRAW);
	
	

	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);

	glBindVertexArray(0);

	glGenVertexArrays(1, &vertex2);
	GLfloat f = 0;
	glBindVertexArray(vertex2);
	glBindBuffer(GL_ARRAY_BUFFER, colorVertexBufferObjects);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_coord), color_coord, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glClearColor(1.f, 1.f, 1.f, 0.f);

	 std::shared_ptr<Renderer::ShaderProgram> shaderProgram = manager.GetShaderProgram("default");

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram->Use();

		GLint uniform = glGetUniformLocation(shaderProgram->GetID(), "vertexColor");
		glUniform4f(uniform, 1.f, -0.5f, 0.5f, 1.f);
		/*GLint uniformPos = glGetUniformLocation(shaderProgram->GetID(), "pos");
		f = sin(glfwGetTime()) / 2 + 0.5f;
		glUniform1f(uniformPos, f);
		*/
		glBindVertexArray(vertex2);
		
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(vertexArrayObjects);
		
		glDrawArrays(GL_TRIANGLES, 0, 3);



		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}