#pragma once
#include <string>
#include <map>
#include <list>

typedef struct GLFWwindow;
typedef unsigned int GLuint;

namespace Vortex
{
	namespace Graphics {

#define VR VRenderer::Instance()

		typedef enum ShaderType {VERTEX, FRAGMENT, GEOMETRY};

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

			void CompileShader(ShaderType shaderMode, const char *shaderPath);
			void SetupShaderProgram(const char* newProgramName);
			void UseShaderProgram(const char* programName);

			unsigned int GetShaderProgram(char* name);

		private:
			VRenderer();

			GLFWwindow* window;

			std::list<unsigned int> compiledShaders;
			std::map<const char*, unsigned int> shaderPrograms;
			
		};

		void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	}	
}
