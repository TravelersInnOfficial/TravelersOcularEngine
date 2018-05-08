#ifndef TFMESH_H
#define TFMESH_H

#include "TFNode.h"

class TFMesh: public TFNode{
	friend class SceneManager;

public:
	void SetTexture(std::string texturePath = "");		// Replaces the Texture with a new one
	void SetSpecularMap(std::string texturePath = ""); 	// Replaces the specular map
	void SetBumpMap(std::string texturePath = ""); 		// Replaces the bump map
	void SetMesh(std::string meshPath = "");			// Replaces the Mesh with a new one
	void CreateCube();									// Replaces the Mesh with a Cube
	void CreateSphere();								// Replaces the Mesh with a Sphere
	void SetInvisible();								// Assigns and invisible texture (0,0,0,0)
	void SetBoundBox(bool visible) override;			// Shows or hide tmesh bounding box
	void SetTextureScale(float valueX, float valueY);

protected:
	TFMesh(
		TOEvector3df position = TOEvector3df(0, 0, 0),
		TOEvector3df rotation = TOEvector3df(0, 0, 0),
		TOEvector3df scale = TOEvector3df(1, 1, 1),
		std::string meshPath = ""
	);
	~TFMesh();

};

#endif