#ifndef TFMESH_H
#define TFMESH_H

#include "TFNode.h"

class TFMesh: public TFNode{
public:
	TFMesh(
		vector3df position = vector3df(0, 0, 0),
		vector3df rotation = vector3df(0, 0, 0),
		vector3df scale = vector3df(0, 0, 0),
		std::string meshPath = ""
	);
	~TFMesh();

	void CreateEstructure();

	void SetScale(vector3df scale);			// Sets the scale of the Node
	void Scale(vector3df scale);			// Adds the scale to the current scale

	void SetTexture(std::string texturePath = "");		// Replaces the Texture with a new one
	void SetMesh(std::string meshPath = "");			// Replaces the Mesh with a new one

	void CreateCube();						// Replaces the Mesh with a Cube

private:
	TNode* m_scaleNode;

};

#endif