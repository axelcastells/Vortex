// VortexGame.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <Renderer.h>
#include <Input.h>
#include <VMath.h>

using namespace Vortex;
using namespace Graphics;
using namespace Input;
int main()
{
	const char* buff = "mainBuffer";
	const char* prog = "mainProgram";

	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 2,   // first triangle
		0, 2, 3    // second triangle
	};

	VR->Init(500, 500, "VortexEngine - Game Window");
	
	VR->CreateShader(prog, ".\\vertexShader", ".\\fragmentShader");
	Material mat = Material(VR->GetShader(prog));
	mat.tex = Texture(".\\tex.jpg");
	VR->BindAndSetBuffers(buff, vertices, 32, indices, 6);
	//Vector3 vec;
	while (!VR->WindowShouldClose()) {
		// Input Event Managing
		VI->ProcessInput(VR->GetWindow());
		// Update Loop
		//vec = Vector3(vertices[0], vertices[1], vertices[2]);
		//vec = Math::Translate(vec, Vector3(0.00001f, 0, 0));
		//vertices[0] = vec.x;
		//vertices[1] = vec.y;
		//vertices[2] = vec.z;

		//std::cout << "Vertices: x: " << vertices[0] << " | y: " <<
		//	vertices[1] << " | z: " << vertices[2] << std::endl;

		// Draw Loop
		VR->ClearScreen(0.3f, 0.3f, 0.3f, 1);

		DrawElements(VR->GetBuffer(buff), &mat);
		
		// Swaping
		VR->SwapBuffers();
		VI->PollEvents();
	}

	VR->Terminate();
}