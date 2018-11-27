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

	VR->Init(800, 900, "VortexEngine - Game Window");
	//VR->Run();

	
	VR->CompileShader(ShaderType::VERTEX, ".\\vertexshader");
	VR->CompileShader(ShaderType::FRAGMENT, ".\\fragmentshader");

	VR->SetupShaderProgram("mainProgram");

	float vertices[] = {
	-0.5f, -0.5f, 0.0f,	// left
	 0.5f, -0.5f, 0.0f,	// right
	 0.0f,  0.5f, 0.0f	// up
	};
	VR->BindAndSetBuffers(buff, vertices);

	while (!VR->WindowShouldClose()) {
		VI->ProcessInput(VR->GetWindow());

		VR->ClearScreen(0.3f, 0.3f, 0.3f, 1);

		VR->UseShaderProgram("mainProgram");

		DrawTriangle(VR->GetBufferData(buff), vertices);
		
		VR->SwapBuffers();
		VI->PollEvents();
	}

	VR->Terminate();
	
	system("pause");
}
// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
