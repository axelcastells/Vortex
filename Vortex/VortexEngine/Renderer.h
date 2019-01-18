#pragma once
#include <string>
#include <map>
#include <list>
#include "Vector.h"
#include "Shader.h"

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

			void CreateShader(const char *nameId, const char *vertexPath, const char *fragmentPath);
			Shader *GetShader(const char *name);
			Buffer *GetBuffer(const char* name);

			//template<typename T>
			void BindAndSetBuffers(const char* bufferId, void* vertices, int verticesArrayCount, void* indices, int indicesArrayCount);

		private:
			VRenderer();

			GLFWwindow* window;

			std::map<const char*, Buffer> buffers;
			std::map<const char*, Shader> shaders;
			
		};

		
		void DrawElements(Buffer* buff);

		void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	}	
}
