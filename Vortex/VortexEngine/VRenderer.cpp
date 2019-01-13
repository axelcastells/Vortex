#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <iostream>
#include <vector>

#include "Renderer.h"
#include "Input.h"
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
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		//Error
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
}

unsigned int VRenderer::GetShaderProgram(const char* name) {
	return shaderPrograms[name];
}

Buffer* VRenderer::GetBufferData(const char* name) {
	return &buffers[name];
}

bool VRenderer::WindowShouldClose() {
	return glfwWindowShouldClose(window);
}

void VRenderer::Run() {

	CompileShader(ShaderType::VERTEX, ".\\vertexshader");
	CompileShader(ShaderType::FRAGMENT, ".\\fragmentshader");

	SetupShaderProgram("mainProgram");


	float vertices[] = {
		-0.5f, -0.5f, 0.0f,	// left
		 0.5f, -0.5f, 0.0f,	// right
		 0.0f,  0.5f, 0.0f	// up
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		// Input
		VI->ProcessInput(window);

		// Rendering
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		UseShaderProgram("mainProgram");
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// Unbind VAO, but no need to do it every time
		glBindVertexArray(0);


		// Events check and buffers swaping
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
}

GLFWwindow* VRenderer::GetWindow() {
	return window;
}

void VRenderer::SwapBuffers() {
	glfwSwapBuffers(window);
}

void VRenderer::Terminate() {
	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);

	glfwTerminate();
}

void Vortex::Graphics::DrawTriangle(Buffer* buff, void* vertexArray) {

	glBindVertexArray(buff->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}

//template<typename T>
void VRenderer::BindAndSetBuffers(const char* bufferId, void* data) {
	Buffer buff;
	glGenVertexArrays(1, &buff.VAO);
	glGenBuffers(1, &buff.VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(buff.VAO);
	float vertices[] = {
-0.5f, -0.5f, 0.0f,	// left
 0.5f, -0.5f, 0.0f,	// right
 0.0f,  0.5f, 0.0f	// up
	};
	glBindBuffer(GL_ARRAY_BUFFER, buff.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	buffers.insert(std::pair<const char*, Buffer>(bufferId, buff));
}

void Vortex::Graphics::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void VRenderer::CompileShader(ShaderType shaderMode, const char *shaderPath) {
	std::string str = DataManager::FileManager::ReadFile(shaderPath);
	const char* shaderSrc = str.c_str();
	
	unsigned int shader;
	switch (shaderMode)
	{
	case Vortex::Graphics::VERTEX: {
		shader = glCreateShader(GL_VERTEX_SHADER);
	}
		break;
	case Vortex::Graphics::FRAGMENT: {
		shader = glCreateShader(GL_FRAGMENT_SHADER);
	}
		break;
	case Vortex::Graphics::GEOMETRY: {
		shader = glCreateShader(GL_GEOMETRY_SHADER);
	}
		break;
	default:
		break;
	}	

	glShaderSource(shader, 1, &shaderSrc, NULL);
	glCompileShader(shader);

	int success;
	char infoLog[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	compiledShaders.push_back(shader);
}

// Creates and links the shader program using all compiled shaders in compiledShaders list
// shaderNames is a pointer to char array
void VRenderer::SetupShaderProgram(const char* newProgramName) {
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	for (std::list<unsigned int>::iterator it = compiledShaders.begin(); it != compiledShaders.end(); it++)
	{
		glAttachShader(shaderProgram, *it);
		glDeleteShader(*it);
	}
	glLinkProgram(shaderProgram);

	int success;
	char infoLog[512];

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	}

	compiledShaders.clear();
	shaderPrograms.insert(std::pair<const char*, unsigned int>(newProgramName, shaderProgram));
}

void VRenderer::UseShaderProgram(const char* programName) {
	glUseProgram(shaderPrograms[programName]);
}

void VRenderer::ClearScreen(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}