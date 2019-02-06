// VortexGame.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <Renderer.h>
#include <Input.h>

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

	while (!VR->WindowShouldClose()) {
		// Input Event Managing
		VI->ProcessInput(VR->GetWindow());

		// Update Loop

		// Draw Loop
		VR->ClearScreen(0.3f, 0.3f, 0.3f, 1);

		DrawElements(VR->GetBuffer(buff), &mat);
		
		// Swaping
		VR->SwapBuffers();
		VI->PollEvents();
	}

	VR->Terminate();
}