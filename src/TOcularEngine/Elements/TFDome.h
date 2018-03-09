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
		toe::core::TOEvector3df position = toe::core::TOEvector3df(0, 0, 0),
		toe::core::TOEvector3df rotation = toe::core::TOEvector3df(0, 0, 0),
		toe::core::TOEvector3df scale = toe::core::TOEvector3df(1.0f, 1.0f, 1.0f),
		std::string meshPath = "",
		std::string texturePath = ""
	);
	~TFDome();

};

#endif