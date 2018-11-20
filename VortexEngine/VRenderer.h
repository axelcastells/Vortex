#pragma once
#include <string>

typedef struct GLFWwindow;

namespace Vortex
{
	namespace Graphics {

#define VR VRenderer::Instance()

		class VRenderer
		{
		public:
			VRenderer(VRenderer const&) = delete;
			VRenderer& operator=(VRenderer const&) = delete;
			~VRenderer();

			static std::shared_ptr<VRenderer> Instance() {
				static std::shared_ptr<VRenderer> instance{ new VRenderer };
				return instance;
			}

			void Init(int w, int h, const char* windowTitle);
			void Run();

		private:
			VRenderer();

			GLFWwindow* window;

			void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
		};
	}	
}
