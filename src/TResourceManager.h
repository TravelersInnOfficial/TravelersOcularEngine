#ifndef TRESOURCEMANAGER_H
#define TRESOURCEMANAGER_H

#include "./Resources/TResource.h"

#include <iostream>
#include <vector>
#include <map>

class TResourceManager{
public:
	
	~TResourceManager();
	
	static TResourceManager* GetInstance();	//Singleton class

	TResource* FindResource(std::string);

	//****************** Getters ******************
	TResource* GetResourceTexture(std::string);
	TResource* GetResourceMesh(std::string);
	TResource* GetResourceMaterial(std::string);
	TResource* GetResourceShader(std::string);
	//*********************************************

	/********************************************
	 * @brief  Modifies the name of the resource
	 * @param  std::string newName for the resource
	 ********************************************/
	std::string TreatName(std::string newName);

private:
	TResourceManager();
	std::map<std::string, TResource*> m_resources;
	
};

#endif