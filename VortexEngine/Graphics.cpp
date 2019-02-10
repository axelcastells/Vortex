#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <iostream>
#include <vector>

#include "Graphics.h"
#include "Input.h"
#include "ResourcesManager.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Vortex::Graphics;
using namespace Vortex::Input;

VEngine::VEngine() {

}

VEngine::~VEngine() {
	delete &window;
}

void VEngine::Init(int w, int h, const char* windowTitle) {
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

//void Vortex::Graphics::VEngine::CreateShader(const char * nameId, const char * vertexPath, const char * fragmentPath)
//{
//	shaders.insert(std::pair<const char*, Shader>(nameId, Shader(vertexPath, fragmentPath)));
//}

//Shader *Vortex::Graphics::VEngine::GetShader(const char *name)
//{
//	return &shaders[name];
//	// TODO: insertar una instrucción return aquí
//}

//Buffer* VEngine::GetBuffer(const char* name) {
//	return &buffers[name];
//}

bool VEngine::WindowShouldClose() {
	return glfwWindowShouldClose(window);
}

GLFWwindow* VEngine::GetWindow() {
	return window;
}

void VEngine::SwapBuffers() {
	glfwSwapBuffers(window);
}

void VEngine::Terminate() {
	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);

	glfwTerminate();
}

//void Vortex::Graphics::SetTransformations(Shader &shader, float width, float height)
//{
//	// Transformations
//	glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//	glm::mat4 view = glm::mat4(1.0f);
//	glm::mat4 projection = glm::mat4(1.0f);
//	model = glm::rotate(model, glm::radians(-55.0f) * (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f));
//	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
//	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
//	// retrieve the matrix uniform locations
//	unsigned int modelLoc = glGetUniformLocation(shader.GetID(), "model");
//	unsigned int viewLoc = glGetUniformLocation(shader.GetID(), "view");
//	unsigned int projectionLoc = glGetUniformLocation(shader.GetID(), "projection");
//	// pass them to the shaders (3 different ways)
//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
//	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
//	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
//}

//void Vortex::Graphics::DrawElements(Buffer* buff, Material* mat) {
//	// TODO: Bind all textures in material
//	glEnable(GL_DEPTH_TEST);
//	glBindTexture(GL_TEXTURE_2D, mat->tex.GetID());
//
//	glBindVertexArray(buff->VBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buff->EBO);
//
//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//	//glDrawArrays(GL_TRIANGLES, 0, 3);
//	glBindVertexArray(0);
//}

//void VEngine::BindAndSetBuffers(const char* bufferId, void* vertices, int verticesArrayCount, void* indices, int indicesArrayCount) {
//	Buffer buff;
//	glGenVertexArrays(1, &buff.VAO);
//	glGenBuffers(1, &buff.VBO);
//	glGenBuffers(1, &buff.EBO);
//
//	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
//
//	// 1. bind Vertex Array Objects
//	glBindVertexArray(buff.VAO);
//	// 2. copy our vertices array in a vertex buffer for OpenGL to use
//	glBindBuffer(GL_ARRAY_BUFFER, buff.VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices)*verticesArrayCount, vertices, GL_STATIC_DRAW);
//	// 3. copy our index array in a element buffer for OpenGL to use
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buff.EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices)*indicesArrayCount, indices, GL_STATIC_DRAW);
//	// 4. then set the vertex attributes pointers
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	// Color attributes pointers
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//	// Texture attributes pointers
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//	glEnableVertexAttribArray(2);
//
//	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
//	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
//	glBindVertexArray(0);
//	
//	buffers.insert(std::pair<const char*, Buffer>(bufferId, buff));
//}

void Vortex::Graphics::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// Creates and links the shader program using all compiled shaders in compiledShaders list
// shaderNames is a pointer to char array

void VEngine::ClearScreen(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	//glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}