#ifndef TFMESH_H
#define TFMESH_H

#include "TFNode.h"

class TFMesh: public TFNode{
	friend class SceneManager;

public:
	void SetTexture(std::string texturePath = "");		// Replaces the Texture with a new one
	void SetMesh(std::string meshPath = "");			// Replaces the Mesh with a new one
	void CreateCube();									// Replaces the Mesh with a Cube
	void CreateSphere();								// Replaces the Mesh with a Sphere
	void SetInvisible();								// Assigns and invisible texture (0,0,0,0)
	void SetBoundBox(bool visible) override;							// Shows or hide tmesh bounding box

protected:
	TFMesh(
		toe::core::TOEvector3df position = toe::core::TOEvector3df(0, 0, 0),
		toe::core::TOEvector3df rotation = toe::core::TOEvector3df(0, 0, 0),
		toe::core::TOEvector3df scale = toe::core::TOEvector3df(0, 0, 0),
		std::string meshPath = ""
	);
	~TFMesh();

};

#endif