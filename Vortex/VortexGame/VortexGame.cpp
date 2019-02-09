// VortexGame.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <Graphics.h>
#include <Input.h>
#include <VMath.h>
#include <Entity.h>
#include <Renderer.h>

using namespace Vortex;
using namespace Graphics;
using namespace Input;
int main()
{
	//const char* buff = "mainBuffer";
	//const char* prog = "mainProgram";

	//float vertices[] = {
	//-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	// 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	// 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	// 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	//-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	//-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	//-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	// 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	// 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	// 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	//-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	//-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	//-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	//-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	//-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	//-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	//-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	//-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	// 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	// 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	// 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	// 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	// 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	// 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	//-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	// 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	// 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	// 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	//-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	//-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	//-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	// 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	// 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	// 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	//-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	//-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	//};
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
	
	//VR->CreateShader(prog, ".\\vertexShader", ".\\fragmentShader");
	//Material mat = Material(new Shader(".\\vertexShader", ".\\fragmentShader"));
	//mat.tex = Texture(".\\tex.jpg");
	//VR->BindAndSetBuffers(buff, vertices, 32, indices, 6);
	//Vector3 vec;

	Renderer r;
	r = Renderer();
	r.SetMaterial(new Material(new Shader(".\\vertexShader", ".\\fragmentShader")));
	r.GetMaterial().tex = Texture(".\\tex.jpg");
	r.SetMeshData(vertices, 32, indices, 6);

	while (!VR->WindowShouldClose()) {
		// Input Event Managing
		VI->ProcessInput(VR->GetWindow());
		// Update Loop
		r.Update();
		//mat.GetShader().Use();

		// Transformations
		//SetTransformations(mat.GetShader(), 500, 500);

		

		// Draw Loop
		VR->ClearScreen(0.3f, 0.3f, 0.3f, 1);
		r.Draw();
		//DrawElements(VR->GetBuffer(buff), &mat);
		
		// Swaping
		VR->SwapBuffers();
		VI->PollEvents();
	}

	VR->Terminate();
}