#ifndef TRESOURCEMANAGER_H
#define TRESOURCEMANAGER_H

/**
 * @brief ResourceManager will load all resources and control
 * 		  that resources only are read once.
 * 
 * @file TResourceManager.h
 */

#include "Resources/TResource.h"
#include "Resources/TResourceTexture.h"
#include "Resources/TResourceMesh.h"
#include "Resources/TResourceShader.h"
#include "Resources/TResourceMaterial.h"

#include <vector>
#include <map>
#include <string>
#include <GL/glew.h>

class TResourceManager{
public:
	/*********************************************
	 * @brief Destructor
	 *********************************************/
	~TResourceManager();
	
	/**
	 * @brief Get the curren singleton instance
	 */
	static TResourceManager* GetInstance();	//Singleton class

	//****************** Getters ******************
	TResourceTexture*	GetResourceTexture	(std::string name);
	TResourceMesh*		GetResourceMesh		(std::string name);
	TResourceMaterial*	GetResourceMaterial	(std::string name);
	TResourceShader* 	GetResourceShader	(std::string name, GLenum shaderType);
	//*********************************************

	/**
	 * @brief	- Elimina el recurso pasado por parametros 
	 * 
	 * @param 	- path - Ruta del recurso a eliminar 
	 * @return 	- bool - Si se ha eliminado correctamente el recurso
	 */
	bool DeleteResourceTexture(std::string path);

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

	std::map<std::string, TResource*> m_resources;	// m_resources - mapa con todos los recursos ordenados por la ruta
	
};

#endif