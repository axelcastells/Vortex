#pragma once
#include <string>
#include <map>
#include <list>
#include "Vector.h"
#include "Shader.h"
#include "Camera.h"

#include "Material.h"

typedef struct GLFWwindow;
typedef unsigned int GLuint;

namespace Vortex
{
	namespace Graphics {
		//struct Buffer {
		//	unsigned int VAO, VBO, EBO;
		//};
#define VE VortexEngine::Instance()

		class VortexEngine
		{
		public:
			VortexEngine(VortexEngine const&) = delete;
			VortexEngine& operator=(VortexEngine const&) = delete;
			~VortexEngine();

			static std::shared_ptr<VortexEngine> Instance() {
				static std::shared_ptr<VortexEngine> instance{ new VortexEngine };
				return instance;
			}

			void Init(int w, int h, const char* windowTitle);
			void Terminate();

			bool WindowShouldClose();
			void ClearScreen(float r, float g, float b, float a);
			void SwapBuffers();

			GLFWwindow* GetWindow();

			//void CreateShader(const char *nameId, const char *vertexPath, const char *fragmentPath);
			//Shader *GetShader(const char *name);
			//Buffer *GetBuffer(const char* name);

			/// Bind and set buffers as GL_ELEMENT_ARRAY_BUFFER
			//void BindAndSetBuffers(const char* bufferId, void* vertices, int verticesArrayCount, void* indices, int indicesArrayCount);
		private:
			VortexEngine();

			GLFWwindow* window;

			//std::map<const char*, Buffer> buffers;
			//std::map<const char*, Shader> shaders;
			
		};

		//void SetTransformations(Shader &shader, float width, float height);
		
		//void DrawElements(Buffer* buff, Material* tex);

		void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	}	
}
