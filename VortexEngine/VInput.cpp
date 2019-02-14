#include <GLFW\glfw3.h>
#include <memory>

#include "Input.h"

using namespace Vortex::Input;

VInput::VInput() {

}

VInput::~VInput() {

}

void VInput::PollEvents() {
	glfwPollEvents();
}

void VInput::ProcessInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}