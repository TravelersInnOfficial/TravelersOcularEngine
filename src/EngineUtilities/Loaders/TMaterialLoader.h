#ifndef TMATERIALLOADER_H
#define TMATERIALLOADER_H

#include "./../Resources/TResourceMesh.h"
#include <string>
class aiMaterial;

class TMaterialLoader{
public:
	static bool LoadMaterial(std::string name, std::string path, TResourceMesh* mesh);
	static bool LoadMaterial(std::string name, TResourceMesh* mesh, const aiMaterial* material);
private:
	static void Read3Elements(float* value1, float* value2, float* value3, std::string line);
	static std::string TreatPath(std::string pathObj);
};

#endif