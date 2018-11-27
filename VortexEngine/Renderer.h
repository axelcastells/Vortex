#pragma once
#include <string>
#include <map>
#include <list>
#include "DataTypes.h"

typedef struct GLFWwindow;
typedef unsigned int GLuint;

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
			void Terminate();

			bool WindowShouldClose();
			void ClearScreen(float r, float g, float b, float a);
			void SwapBuffers();

			GLFWwindow* GetWindow();

			void CompileShader(ShaderType shaderMode, const char *shaderPath);
			void SetupShaderProgram(const char* newProgramName);
			void UseShaderProgram(const char* programName);

			unsigned int GetShaderProgram(const char* name);
			Buffer* GetBufferData(const char* name);

			//template<typename T>
			void BindAndSetBuffers(const char* bufferId, void* data);

		private:
			VRenderer();

			GLFWwindow* window;

			std::map<const char*, Buffer*> buffers;
			std::list<unsigned int> compiledShaders;
			std::map<const char*, unsigned int> shaderPrograms;
			
		};

		
		void DrawTriangle(Buffer* buff, void* vertexArray);

		void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	}	
}
