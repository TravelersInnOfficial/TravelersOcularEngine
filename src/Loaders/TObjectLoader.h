#ifndef TOBJECTLOADER_H
#define TOBJECTLOADER_H

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

class TObjectLoader{
public:
	static bool LoadObjAssimp(TResourceMesh* mesh);
	static bool LoadObjCustom(TResourceMesh* mesh);
	static bool LoadObj(TResourceMesh* mesh, int option);
private:
	static bool LoadObjFromFileCustom(TResourceMesh* mesh, std::vector<glm::vec3>* vertex, std::vector<glm::vec2>* uv, std::vector<glm::vec3>* normal);
	static bool LoadObjFromFileAssimp(TResourceMesh* mesh, std::vector<glm::vec3>* vertex, std::vector<glm::vec2>* uv, std::vector<glm::vec3>* normal);
	static void IndexVBO(TResourceMesh* mesh, std::vector<glm::vec3>* vertex, std::vector<glm::vec2>* uv, std::vector<glm::vec3>* normal, std::vector<unsigned int>* index);
	static bool GetSimilarVertexIndex_fast(PackedVertex* packed, std::map<PackedVertex,unsigned int>* VertexToOutIndex, unsigned int* result);
};

#endif