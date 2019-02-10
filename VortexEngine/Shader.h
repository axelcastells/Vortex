#pragma once
#include <string>
#include "VMath.h"

class Shader
{
public:
	// constructor reads and builds the shader
	Shader() {};
	Shader(const char* vertexPath, const char* fragmentPath);
	// use/activate the shader
	void Use();
	// utility uniform functions
	void SetBool(const std::string &name, bool value) const;
	void SetInt(const std::string &name, int value) const;
	void SetFloat(const std::string &name, float value) const;
	unsigned int GetID();

private:
	// the program ID
	unsigned int id;

	void CheckCompileErrors(unsigned int shader, std::string type);
};