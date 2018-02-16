#ifndef TASSIMPLOADER_H
#define TASSIMPLOADER_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "./../Resources/TResourceMesh.h"

class TAssimpLoader{
public:
	static bool LoadObj(std::string path, std::vector<glm::vec3>* out_vertices, std::vector<glm::vec2>* out_uvs, std::vector<glm::vec3>* out_normals);
private:

};

#endif