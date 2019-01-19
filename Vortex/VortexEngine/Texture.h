#pragma once
#include <iostream>

class Texture {
public:
	Texture(const char * filePath);
	unsigned int GetID();


private:
	int width, height, nrChannels;
	unsigned int id;
};