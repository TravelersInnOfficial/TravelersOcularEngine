#ifndef TOBJECTLOADER_H
#define TOBJECTLOADER_H

#include "./../Resources/TResourceMesh.h"
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <vector>
#include <map>

struct PackedVertex{
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec3 normal;
	bool operator<(const PackedVertex that) const;
};

class TObjectLoader{
public:
	static bool LoadObjAssimp(TResourceMesh* mesh, std::vector<glm::vec3>* vertex);
	static bool LoadObjCustom(TResourceMesh* mesh, std::vector<glm::vec3>* vertex);
	static bool LoadObj(TResourceMesh* mesh, std::vector<glm::vec3>* vertex, int option);
private:
	static bool LoadObjFromFileCustom(TResourceMesh* mesh, std::vector<glm::vec3>* vertex, std::vector<glm::vec2>* uv, std::vector<glm::vec3>* normal);
	static bool LoadObjFromFileAssimp(TResourceMesh* mesh, std::vector<glm::vec3>* vertex, std::vector<glm::vec2>* uv, std::vector<glm::vec3>* normal);
	static void IndexVBO(TResourceMesh* mesh, std::vector<glm::vec3>* vertex, std::vector<glm::vec2>* uv, std::vector<glm::vec3>* normal, std::vector<unsigned int>* index);
	static bool GetSimilarVertexIndex_fast(PackedVertex* packed, std::map<PackedVertex,unsigned int>* VertexToOutIndex, unsigned int* result);
};

#endif