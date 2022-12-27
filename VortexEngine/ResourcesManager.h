#pragma once
#include <string>


namespace ResourcesManager {
	static class FileManager {
	public:
		static std::string ReadFile(const char* filePath);
	};	
}