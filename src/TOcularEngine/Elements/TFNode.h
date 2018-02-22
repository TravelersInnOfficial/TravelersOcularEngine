#ifndef TFNODE_H
#define TFNODE_H

#include <vector3d.h>
#include "./../../TNode.h"
#include "./../../Entities/TTransform.h"
#include "./../../Entities/TMesh.h"
#include "./../../Entities/TLight.h"
#include "./../../Entities/TCamera.h"

class TFNode{
public:
	TFNode();
	~TFNode();

	virtual void CreateEstructure() = 0;	// Rotacion Escala Translacion

	void SetTranslate();	// Sets the rotation of the Node
	void SetRotation();		// Sets the position of the Node

	void Translate();		// Adds the position to the current position
	void Rotate();			// Adds the rotation to the current rotation

protected:
	TNode* m_meshNode;
	TNode* m_rotationNode;
	TNode* m_positionNode;

};

#endif