#ifndef TFMESH_H
#define TFMESH_H

#include "TFNode.h"

class TFMesh: public TFNode{
	friend class SceneManager;

public:
	void SetScale(toe::core::vector3df scale);			// Sets the scale of the Node
	void Scale(toe::core::vector3df scale);			// Adds the scale to the current scale
	toe::core::vector3df GetScale();					// Returns the scale of the Node

	void SetTexture(std::string texturePath = "");		// Replaces the Texture with a new one
	void SetMesh(std::string meshPath = "");			// Replaces the Mesh with a new one

	void CreateCube();						// Replaces the Mesh with a Cube

private:
	TNode* m_scaleNode;

	TFMesh(
		toe::core::vector3df position = toe::core::vector3df(0, 0, 0),
		toe::core::vector3df rotation = toe::core::vector3df(0, 0, 0),
		toe::core::vector3df scale = toe::core::vector3df(0, 0, 0),
		std::string meshPath = ""
	);
	~TFMesh();
	void CreateEstructure();

};

#endif