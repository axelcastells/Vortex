#pragma once
#include <string>
#include <iostream>
#include <fstream>

namespace DataManager {
	static class FileManager {
	public:
		static const char* ReadFile(const char* filePath);
	};	
}