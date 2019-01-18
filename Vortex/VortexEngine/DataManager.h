#pragma once
#include <string>


namespace DataManager {
	static class FileManager {
	public:
		static std::string ReadFile(const char* filePath);
	};	
}