#ifndef TTEXTURELOADER_H
#define TTEXTURELOADER_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <SOIL/SOIL.h>

#include "./../Resources/TResourceTexture.h"

class TTextureLoader{
public:
	static bool LoadTexture(std::string path, std::vector<glm::vec3>* out_vertices, std::vector<glm::vec2>* out_uvs, std::vector<glm::vec3>* out_normals,std::vector<unsigned int>* out_indices);

private:
	
};

#endif