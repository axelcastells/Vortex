#pragma once
#include <GLFW\glfw3.h>
#include <memory>

namespace Vortex {
	namespace Input {

#define VI VInput::Instance()

		class VInput {
		public:
			VInput(VInput const&) = delete;
			VInput& operator=(VInput const&) = delete;
			~VInput();

			static std::shared_ptr<VInput> Instance() {
				static std::shared_ptr<VInput> instance{ new VInput };
				return instance;
			}

			void ProcessInput(GLFWwindow *window);

		private:
			VInput();
		};
	}
}