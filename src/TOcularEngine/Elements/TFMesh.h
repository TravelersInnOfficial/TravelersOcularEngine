#ifndef TFMESH_H
#define TFMESH_H

/**
 * @brief Mesh Entity Facade.
 * 
 * @file TFMesh.h
 */

#include "TFNode.h"

class TFMesh: public TFNode{
	friend class SceneManager;

public:
	/**
	 * @brief Replaces the Texture with a new one
	 * 
	 * @param texturePath: path from executable
	 */
	void SetTexture(std::string texturePath = "");
	
	/**
	 * @brief Replaces the specular map
	 * 
	 * @param texturePath: path from executable 
	 */
	void SetSpecularMap(std::string texturePath = "");

	/**
	 * @brief Replaces the bump map
	 * 
	 * @param texturePath: path from executable
	 */
	void SetBumpMap(std::string texturePath = "");
	
	/**
	 * @brief Replaces the Mesh with a new one
	 * 
	 * @param meshPath: path from executable
	 */
	void SetMesh(std::string meshPath = "");
	
	/**
	 * @brief Replaces the Mesh with a Cube
	 * 
	 */
	void CreateCube(); 
	
	/**
	 * @brief Replaces the Mesh with a Sphere
	 * 
	 */
	void CreateSphere(); 
	
	/**
	 * @brief Assigns and invisible texture (0,0,0,0)
	 * 
	 */
	void SetInvisible();
	
	/**
	 * @brief Shows or hide tmesh bounding box
	 * 
	 * @param visible: true = visible
	 */
	void SetBoundBox(bool visible) override; 
	
	/**
	 * @brief Set the Texture Mapping Scale
	 * 
	 * @param valueX: size in x
	 * @param valueY: size in y
	 */
	void SetTextureScale(float valueX, float valueY);

protected:

	/**
	 * @brief Construct a new Mesh
	 * 
	 * @param position 
	 * @param rotation 
	 * @param scale 
	 * @param meshPath 
	 */
	TFMesh(
		TOEvector3df position = TOEvector3df(0, 0, 0),
		TOEvector3df rotation = TOEvector3df(0, 0, 0),
		TOEvector3df scale = TOEvector3df(1, 1, 1),
		std::string meshPath = ""
	);

	/**
	 * @brief Destroy the Mesh object
	 * 
	 */
	~TFMesh();

};

#endif