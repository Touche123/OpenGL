#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "Shader.h"
#include "Triangle.h"

int main(int argc, char** argv) {
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
	if (!window) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);

	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	
	Shader shaderManager;

	GLuint vs = shaderManager.LoadShader("assets/shaders/colorShading.vert", GL_VERTEX_SHADER);
	GLuint fs = shaderManager.LoadShader("assets/shaders/colorShading.frag", GL_FRAGMENT_SHADER);
	GLuint shader_programme = shaderManager.CreateProgram(vs, fs);

	Triangle tri;

	glClearColor(0.6f, 0.6f, 0.8f, 1.0f);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader_programme);
		glDrawArrays(GL_LINE_STRIP, 0, 6);
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}