// VortexGame.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <VortexCore.h>

using namespace Vortex;
using namespace Graphics;
using namespace Input;
int main()
{
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

	VE->Init(500, 500, "VortexEngine - Game Window");
	
	long eId;
	Entity &e = ECS->CreateEntity(&eId);
	e.AddComponent<Renderer>();
	e.GetComponent<Renderer>()->Init();
	e.GetComponent<Renderer>()->SetMaterial(new Material(new Shader(".\\vertexShader", ".\\fragmentShader")));
	e.GetComponent<Renderer>()->GetMaterial().tex = Texture(".\\tex.jpg");
	e.GetComponent<Renderer>()->SetMeshData(vertices, 32, indices, 6);

	while (!VE->WindowShouldClose()) {
		// Input Event Managing
		VI->ProcessInput(VE->GetWindow());
		
		// Update Loop
		e.InternalUpdate();

		// Draw Loop
		VE->ClearScreen(0.3f, 0.3f, 0.3f, 1);
		e.InternalDraw();
		
		// Swaping
		VE->SwapBuffers();
		VI->PollEvents();
	}

	VE->Terminate();
}