#include <GLFW\glfw3.h>
#include <glad\glad.h>
#include <iostream>
#include <vector>

#include "VRenderer.h"
#include "VInput.h"
#include "DataManager.h"

using namespace Vortex::Graphics;
using namespace Vortex::Input;

VRenderer::VRenderer() {

}

VRenderer::~VRenderer() {
	delete &window;
}

void VRenderer::Init(int w, int h, const char* windowTitle) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Only for Mac OS X
	
	window = glfwCreateWindow(w, h, windowTitle, NULL, NULL);
	if (window == NULL) {
		//Error
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		//Error
	}

	glViewport(0, 0, w, h);

	//glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
}

void VRenderer::Run() {
	
	while (!glfwWindowShouldClose(window))
	{
		// Input
		VI->ProcessInput(window);

		// Rendering
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		unsigned int VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, ".\\vertexshader");

		unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, ".\\fragmentshader");

		unsigned int shaders[] = { vertexShader, fragmentShader };
		unsigned int shaderProgram = SetupShaderProgram(2, shaders);
		UseShaderProgram(shaderProgram);

		// Events check and buffers swaping
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}

void VRenderer::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

unsigned int VRenderer::CompileShader(unsigned int shaderMode, const char *shaderPath) {
	std::string str = DataManager::FileManager::ReadFile(shaderPath);
	const char* shaderSrc = str.c_str();
	
	unsigned int shader;
	shader = glCreateShader(shaderMode);

	glShaderSource(shader, 1, &shaderSrc, NULL);
	glCompileShader(shader);

	int success;
	char infoLog[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return shader;
}

// Creates and links the shader program
unsigned int VRenderer::SetupShaderProgram(unsigned int size, unsigned int *compiledShaderID) {
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	for (int i = 0; i < size-1; i++)
{
		glAttachShader(shaderProgram, compiledShaderID[i]);
		glDeleteShader(compiledShaderID[i]);
	}
	glLinkProgram(shaderProgram);

	int success;
	char infoLog[512];

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	}

	for (int i = 0; i < size - 1; i++) {
		glDeleteShader(compiledShaderID[i]);
	}

	return shaderProgram;
}

void VRenderer::UseShaderProgram(unsigned int linkedShaderProgram) {
	glUseProgram(linkedShaderProgram);
}