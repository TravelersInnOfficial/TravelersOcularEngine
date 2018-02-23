#ifndef TFNODE_H
#define TFNODE_H

#include <vector3d.h>
#include <TColor.h>
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

	vector3df GetTranslate();					// Returns the rotation of the Node
	vector3df GetRotation();					// Returns the position of the Node

protected:
	TNode* m_entityNode;
	TNode* m_rotationNode;
	TNode* m_positionNode;

	TFNode();
	~TFNode();
	virtual void CreateEstructure() = 0;		// Rotacion Escala Translacion
	void Attach(TNode* root);					// Node to be attached to

};

#endif