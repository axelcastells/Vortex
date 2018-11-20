#include <GLFW\glfw3.h>
#include <glad\glad.h>
#include <ostream>

#include "VRenderer.h"
#include "VInput.h"

using namespace Vortex::Graphics;
using namespace Vortex::Input;

VRenderer::VRenderer() {

}

VRenderer::~VRenderer() {

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

		// Events check and buffers swaping
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}

void VRenderer::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}