#ifndef TFDOME_H
#define TFDOME_H

#include "TFNode.h"

class TFDome: public TFNode{
	friend class SceneManager;
public:
    
    void SetTexture(std::string texturePath = "");		// Replaces the Texture with a new one
	/*
	void SetMesh(std::string meshPath = "");			// Replaces the Mesh with a new one
	void CreateCube();									// Replaces the Mesh with a Cube
	void CreateSphere();								// Replaces the Mesh with a Sphere
    */

private:
	TFDome(
		TOEvector3df position = TOEvector3df(0, 0, 0),
		TOEvector3df rotation = TOEvector3df(0, 0, 0),
		TOEvector3df scale = TOEvector3df(1.0f, 1.0f, 1.0f),
		std::string texturePath = ""
	);
	~TFDome();

};

#endif