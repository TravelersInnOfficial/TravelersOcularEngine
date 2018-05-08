#ifndef TTEXTURELOADER_H
#define TTEXTURELOADER_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <iostream>

#include "./../Resources/TResourceTexture.h"

class TTextureLoader{
public:
	static bool LoadTexture(std::string path, unsigned char** imageData, int* width, int* height);
	static bool LoadTextureBinary(std::string path,  std::vector<unsigned char>* imageData, int* width, int* height);
private:
	
};

#endif