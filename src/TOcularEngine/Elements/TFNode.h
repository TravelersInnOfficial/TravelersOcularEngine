#ifndef TFNODE_H
#define TFNODE_H

#include <vector3d.h>
#include "./../../TNode.h"
#include "./../../Entities/TTransform.h"
#include "./../../Entities/TMesh.h"
#include "./../../Entities/TLight.h"
#include "./../../Entities/TCamera.h"

class SceneManager;

class TFNode{
	friend class SceneManager;

public:
	void SetTranslate(vector3df translation);	// Sets the rotation of the Node
	void SetRotation(vector3df rotation);		// Sets the position of the Node

	void Translate(vector3df translation);		// Adds the position to the current position
	void Rotate(vector3df rotation);			// Adds the rotation to the current rotation

protected:
	TNode* m_meshNode;
	TNode* m_rotationNode;
	TNode* m_positionNode;

	TFNode();
	~TFNode();
	virtual void CreateEstructure() = 0;		// Rotacion Escala Translacion

};

#endif