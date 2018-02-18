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
private:
	static bool LoadObjFromFileCustom(TResourceMesh* mesh);
	static bool LoadObjFromFileAssimp(TResourceMesh* mesh);
	static void IndexVBO(TResourceMesh* mesh);
	static bool GetSimilarVertexIndex_fast(PackedVertex* packed, std::map<PackedVertex,unsigned int>* VertexToOutIndex, unsigned int* result);
};

#endif