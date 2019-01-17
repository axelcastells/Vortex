#pragma once
#include <string>
#include <map>
#include <list>
#include "Vector.h"

typedef struct GLFWwindow;
typedef unsigned int GLuint;

namespace Vortex
{
	namespace Graphics {
		typedef enum ShaderType { VERTEX, FRAGMENT, GEOMETRY };
		struct Buffer {
			unsigned int VAO, VBO, EBO;
		};
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
			void Terminate();

			bool WindowShouldClose();
			void ClearScreen(float r, float g, float b, float a);
			void SwapBuffers();

			GLFWwindow* GetWindow();

			void CompileShader(ShaderType shaderMode, const char *shaderPath);
			void CreateShaderProgram(const char* newProgramName);
			void UseShaderProgram(const char* programName);

			unsigned int GetShaderProgram(const char* name);
			Buffer* GetBufferData(const char* name);

			//template<typename T>
			void BindAndSetBuffers(const char* bufferId, void* vertices, int verticesArrayCount, void* indices, int indicesArrayCount);

		private:
			VRenderer();

			GLFWwindow* window;

			std::map<const char*, Buffer> buffers;
			std::list<unsigned int> compiledShaders;
			std::map<const char*, unsigned int> shaderPrograms;
			
		};

		
		void DrawElements(Buffer* buff);

		void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	}	
}
