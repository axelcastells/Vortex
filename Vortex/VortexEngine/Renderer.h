#pragma once
#include <string>
#include <map>
#include <list>
#include "Vector.h"
#include "Shader.h"

#include "Material.h"

typedef struct GLFWwindow;
typedef unsigned int GLuint;

namespace Vortex
{
	namespace Graphics {
		struct Buffer {
			unsigned int VAO, VBO, EBO;
		};
#define VR VEngine::Instance()

		class VEngine
		{
		public:
			VEngine(VEngine const&) = delete;
			VEngine& operator=(VEngine const&) = delete;
			~VEngine();

			static std::shared_ptr<VEngine> Instance() {
				static std::shared_ptr<VEngine> instance{ new VEngine };
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
			VEngine();

			GLFWwindow* window;

			std::map<const char*, Buffer> buffers;
			std::map<const char*, Shader> shaders;
			
		};

		void SetTransformations(const char* shaderName, float width, float height);
		
		void DrawElements(Buffer* buff, Material* tex);

		void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	}	
}
