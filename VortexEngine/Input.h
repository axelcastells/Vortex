#pragma once


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

			void PollEvents();
			void ProcessInput(GLFWwindow *window);

		private:
			VInput();
		};
	}
}