#include <GLFW\glfw3.h>
#include <memory>

#include "VInput.h"

using namespace Vortex::Input;

VInput::VInput() {

}

VInput::~VInput() {
	delete this;
}

void VInput::ProcessInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}