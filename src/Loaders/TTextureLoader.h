#ifndef TTEXTURELOADER_H
#define TTEXTURELOADER_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <iostream>

#include "./../Resources/TResourceTexture.h"

class TTextureLoader{
public:
	static GLuint LoadTexture(std::string path);

private:
	
};

#endif