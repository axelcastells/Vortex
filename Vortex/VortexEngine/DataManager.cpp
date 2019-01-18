#include "DataManager.h"
#include <sstream>
#include <iostream>
#include <fstream>

using namespace DataManager;

std::string FileManager::ReadFile(const char* filePath) {
	std::ifstream shaderFile;
	try
	{
		// open files
		shaderFile.open(filePath);
		std::stringstream shaderStream;
		// read file's buffer contents into streams
		shaderStream << shaderFile.rdbuf();
		// close file handlers
		shaderFile.close();
		// convert stream into string
		return shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	//std::string content;
	//std::ifstream shaderFile(filePath, std::ios::in);

	//if (!shaderFile.is_open()) {
	//	std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
	//	return "";
	//}

	//std::string line = "";
	//while (!shaderFile.eof()) {
	//	std::getline(shaderFile, line);
	//	content.append(line + "\n");
	//}

	//shaderFile.close();
	//return content.c_str();
}