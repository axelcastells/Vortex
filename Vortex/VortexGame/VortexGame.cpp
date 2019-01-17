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

	VR->Init(500, 500, "VortexEngine - Game Window");
	//VR->Run();

	float vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	float *vptr;
	vptr = vertices;
	
	VR->CompileShader(ShaderType::VERTEX, ".\\vertexshader");
	VR->CompileShader(ShaderType::FRAGMENT, ".\\fragmentshader");

	VR->CreateShaderProgram(prog);

	VR->BindAndSetBuffers(buff, vertices, 12, indices, 6);

	while (!VR->WindowShouldClose()) {
		VI->ProcessInput(VR->GetWindow());

		VR->ClearScreen(0.3f, 0.3f, 0.3f, 1);

		VR->UseShaderProgram(prog);
		DrawElements(VR->GetBufferData(buff));
		
		VR->SwapBuffers();
		VI->PollEvents();
	}

	VR->Terminate();
}
// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
