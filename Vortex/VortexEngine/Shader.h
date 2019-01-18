#pragma once
#include <string>

class Shader
{
public:
	// the program ID
	unsigned int ID;

	// constructor reads and builds the shader
	Shader() {};
	Shader(const char* vertexPath, const char* fragmentPath);
	// use/activate the shader
	void Use();
	// utility uniform functions
	void SetBool(const std::string &name, bool value) const;
	void SetInt(const std::string &name, int value) const;
	void SetFloat(const std::string &name, float value) const;

private:
	void CheckCompileErrors(unsigned int shader, std::string type);
};