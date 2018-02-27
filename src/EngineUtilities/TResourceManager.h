#ifndef TRESOURCEMANAGER_H
#define TRESOURCEMANAGER_H

#include "Resources/TResource.h"
#include "Resources/TResourceTexture.h"
#include "Resources/TResourceMesh.h"
#include "Resources/TResourceShader.h"
#include "Resources/TResourceMaterial.h"

#include <iostream>
#include <vector>
#include <map>

class TResourceManager{
public:
	/*********************************************
	 * @brief Destructor
	 *********************************************/
	~TResourceManager();
	
	/**
	 * @brief Get the curren singleton instance
	 * 
	 */
	static TResourceManager* GetInstance();	//Singleton class

	//****************** Getters ******************
	TResourceTexture*	GetResourceTexture	(std::string name);
	TResourceMesh*		GetResourceMesh		(std::string name);
	TResourceMaterial*	GetResourceMaterial	(std::string name);
	TResourceShader*	GetResourceShader	(std::string name);
	//*********************************************

private:
	TResourceManager();

	/*********************************************
	 * @brief Find the resource of the string passed
	 * @param std::string path of the resource
	 *********************************************/
	TResource* FindResource(std::string);

	/********************************************
	 * @brief  Modifies the name of the resource
	 * @param  std::string newName for the resource
	 ********************************************/
	std::string TreatName(std::string newName);

	std::map<std::string, TResource*> m_resources;
	
};

#endif