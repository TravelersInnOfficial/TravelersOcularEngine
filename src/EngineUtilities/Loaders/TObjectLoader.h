#ifndef TOBJECTLOADER_H
#define TOBJECTLOADER_H

/**
 * @brief Loads all Meshes.
 * 
 * @file TObjectLoader.h
 */

#include "./../Resources/TResourceMesh.h"
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <vector>
#include <map>

/**
 * @brief 	- Struct que se utiliza para saber el numero de elemtos que componen el objeto
 * 				a traves de la posicion, uv, y normal de cada vertice
 */
struct PackedVertex{
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec3 normal;
	bool operator<(const PackedVertex that) const;
};

class TObjectLoader{
public:
	/**
	 * @brief	- Llamamos a que se cargue el obj con Assimp
	 * 
	 * @param 	- mesh - Recurso mesh a cargar
	 * @return 	- bool - El obj se ha cargado correctamente
	 */
	static bool LoadObjAssimp(TResourceMesh* mesh);

	/**
	 * @brief	- Llamamos a que se cague el obj con el cargador personalizado
	 * 
	 * @param 	- mesh - Recurso mesh a cargar 
	 * @return 	- bool - El obj se ha cargado correctamente
	 */
	static bool LoadObjCustom(TResourceMesh* mesh);

	/**
	 * @brief	- Cargamos el obj con el cargador binario
	 * 
	 * @param 	- mesh - Recurso mesh a cargar 
	 * @return 	- bool - El obj se ha cargado correctamente
	 */
	static bool LoadObjBinary(TResourceMesh* mesh);

	/**
	 * @brief 	- Llamamos al cargador de obj pasando el metodo que queremos utilizar
	 * 
	 * @param 	- mesh - Recurso mesh a cargar
	 * @param 	- option - Tipo de carga a utilizar
	 * 
	 * @return 	- bool - El obj se ha cargado correctamente
	 */
	static bool LoadObj(TResourceMesh* mesh, int option);
private:
	/**
	 * @brief	- Cargamos la Bounding Box del mesh 
	 * 
	 * @param 	- mesh - Recurso mesh del que sacar la bounding box
	 * @param 	- vertex - Vertices para calcularlo
	 * 
	 * @return 	- bool - La bounding box se ha cargado correctamente
	 */
	static bool LoadBoundingBox(TResourceMesh* mesh, std::vector<glm::vec3>* vertex);
	
	/**
	 * @brief	- Cargamos el obj utilizando el cargado personalizado 
	 * 
	 * @param 	- mesh - Recurso mesh a cargar 
	 * @param 	- vertex - Vertices del mesh
	 * @param 	- uv - Uvs del mesh
	 * @param 	- normal - Normales del mesh
	 * 
	 * @return	- bool - Se ha cargado el obj correctamente 
	 */
	static bool LoadObjFromFileCustom(TResourceMesh* mesh, std::vector<glm::vec3>* vertex, std::vector<glm::vec2>* uv, std::vector<glm::vec3>* normal);
	
	/**
	 * @brief	- Cargamos el obj utilizando el cargador de assimp 
	 * 
	 * @param 	- mesh - Recurso mesh a cargar
	 * @param 	- vertex - Vertices del mesh
	 * @param 	- uv - Uvs del mesh
	 * @param 	- normal - Normales del mesh
	 * 
	 * @return 	- bool - Se ha cargado el obj correctamente
	 */
	static bool LoadObjFromFileAssimp(TResourceMesh* mesh, std::vector<glm::vec3>* vertex, std::vector<glm::vec2>* uv, std::vector<glm::vec3>* normal);
	
	/**
	 * @brief	- Indexamos los vertices para conseguir los elementos del objeto 
	 * 
	 * @param 	- mesh - Recurso mesh a indexar 
	 * @param 	- vertex - Vertices del mesh
	 * @param 	- uvs - Uvs del mesh
	 * @param 	- normals - Normales del mesh
	 * @param 	- index - Elementos del mesh
	 */
	static void IndexVBO(TResourceMesh* mesh, std::vector<glm::vec3>* vertex, std::vector<glm::vec2>* uv, std::vector<glm::vec3>* normal, std::vector<unsigned int>* index);
	
	/**
	 * @brief	- Miramos si existe un paquete de vertices parecido para calcular los elementos 
	 * 
	 * @param 	- packed - Paquete a comprobar
	 * @param 	- VertexToOutIndex - Mapa de paquetes
	 * @param 	- int - Elemento igual
	 * @return 	- bool - existe un paquete igual
	 */
	static bool GetSimilarVertexIndex_fast(PackedVertex* packed, std::map<PackedVertex,unsigned int>* VertexToOutIndex, unsigned int* result);
};

#endif