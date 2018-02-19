#ifndef TMATERIALLOADER_H
#define TMATERIALLOADER_H

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "./../Resources/TResourceMesh.h"

class TMaterialLoader{
public:
	static bool LoadMaterial(std::string name, TResourceMesh* mesh, const aiMaterial* material);
private:
};

#endif