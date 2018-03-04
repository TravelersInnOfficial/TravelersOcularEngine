#ifndef TMATERIALLOADER_H
#define TMATERIALLOADER_H

#include "./../Resources/TResourceMesh.h"
#include <string>
class aiMaterial;

class TMaterialLoader{
public:
	static bool LoadMaterial(std::string name, TResourceMesh* mesh, const aiMaterial* material);
private:
};

#endif