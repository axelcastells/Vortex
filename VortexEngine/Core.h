#pragma once
#include <string>
#include <GLFW\glfw3.h>
#include <glad\glad.h>

namespace Vortex 
{
	class VRenderer 
	{
	public:
		VRenderer();
		~VRenderer();
		void Init(int w, int h, const char* windowTitle);
		void Run();

	private:
		GLFWwindow* window;

		void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	};
}
