#ifndef TRESOURCEMANAGER_H
#define TRESOURCEMANAGER_H

#include "./Resources/TResource.h"

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
	TResource* GetResourceTexture(std::string);
	TResource* GetResourceMesh(std::string);
	TResource* GetResourceMaterial(std::string);
	TResource* GetResourceShader(std::string);
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