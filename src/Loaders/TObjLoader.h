#ifndef TOBJLOADER_H
#define TOBJLOADER_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <iostream>
#include <stdio.h>
#include <vector>

#include "./../Resources/TResourceMesh.h"

class TObjLoader{
public:
	static bool LoadObj(std::string path, std::vector<glm::vec3>* out_vertices, std::vector<glm::vec2>* out_uvs, std::vector<glm::vec3>* out_normals);
	static bool LoadObj(
		std::string path, 
		std::vector<glm::vec3>* out_vertices, 
		std::vector<glm::vec2>* out_uvs,
		std::vector<glm::vec3>* out_normals,
		std::vector<unsigned int>* out_indices);
private:

};

#endif