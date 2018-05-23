#ifndef TMATERIALLOADER_H
#define TMATERIALLOADER_H

/**
 * @brief Loads all Materials of a Mesh.
 * 
 * @file TMaterialLoader.h
 */

#include "./../Resources/TResourceMesh.h"
#include <string>
class aiMaterial;

class TMaterialLoader{
public:
	/**
	 * @brief	- Cargamos el material a partir de leer el documento a mano 
	 * 
	 * @param 	- name - Nombre del material
	 * @param 	- path - Ruta del obj que tiene el material 
	 * @param 	- mesh - Recurso del mesh que necesita el material 
	 * @return 	- bool - Se ha cargado correctamente el material
	 */
	static bool LoadMaterial(std::string name, std::string path, TResourceMesh* mesh);
	
	/**
	 * @brief	- Cargamos el material a partir del objeto material que nos pasa assimp 
	 * 
	 * @param 	- name - Nombre del material 
	 * @param 	- mesh - Recurso del mesh que necesita el material 
	 * @param 	- material - Objeto material de assimp 
	 * @return 	- bool - Se ha cargado correctamente el material
	 */
	static bool LoadMaterial(std::string name, TResourceMesh* mesh, const aiMaterial* material);
private:
	/**
	 * @brief	- Leemos los primero tres floats del string pasado por parametros 
	 * 
	 * @param 	- value1 - Primer valor a leer 
	 * @param 	- value2 - Segundo valor a leer 
	 * @param 	- value3 - Tercer valor a leer 
	 * @param 	- line - Cadena de donde sacar los valores 
	 */
	static void Read3Elements(float* value1, float* value2, float* value3, std::string line);
	
	/**
	 * @brief	- Cambiamos el string pasado por parametros de .obj a .mtl 
	 * 
	 * @param 	- pathObj - Path del obj 
	 * @return	- std::string - Path tratado 
	 */
	static std::string TreatPath(std::string pathObj);
};

#endif