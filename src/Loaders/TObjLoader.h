#ifndef TASSIMPLOADER_H
#define TASSIMPLOADER_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <fstream>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "./../Resources/TResourceMesh.h"

struct PackedVertex{
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec3 normal;
	bool operator<(const PackedVertex that) const{
		return memcmp((void*)this, (void*)&that, sizeof(PackedVertex))>0;
	};
};

class TObjLoader{
public:
	static bool LoadObjAssimp(
		std::string path, 
		std::vector<glm::vec3>* out_vertices, 
		std::vector<glm::vec2>* out_uvs, 
		std::vector<glm::vec3>* out_normals,
		std::vector<unsigned int>* out_indices);
	static bool LoadObjCustom(
		std::string path, 
		std::vector<glm::vec3>* out_vertices, 
		std::vector<glm::vec2>* out_uvs,
		std::vector<glm::vec3>* out_normals,
		std::vector<unsigned int>* out_indices);
private:
	static bool LoadObjFromFileCustom(std::string path, std::vector<glm::vec3>* out_vertices, std::vector<glm::vec2>* out_uvs, std::vector<glm::vec3>* out_normals);
	static bool LoadObjFromFileAssimp(std::string path, std::vector<glm::vec3>* out_vertices, std::vector<glm::vec2>* out_uvs, std::vector<glm::vec3>* out_normals);
	static void IndexVBO(std::vector<glm::vec3>* out_vertices, std::vector<glm::vec2>* out_uvs, std::vector<glm::vec3>* out_normals, std::vector<unsigned int>* out_indices);
	static bool GetSimilarVertexIndex_fast(PackedVertex* packed, std::map<PackedVertex,unsigned int>* VertexToOutIndex, unsigned int* result);
};

#endif