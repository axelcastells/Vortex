#pragma once
#include <string>
#include <iostream>
#include <fstream>

namespace DataManager {
	static class FileManager {
	public:
		static std::string ReadFile(const char* filePath);
	};	
}