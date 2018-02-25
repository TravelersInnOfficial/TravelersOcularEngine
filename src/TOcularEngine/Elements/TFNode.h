#ifndef TFNODE_H
#define TFNODE_H

#include <vector3d.h>
#include <TColor.h>
#include <glm/gtx/matrix_decompose.hpp>
#include "./../../TNode.h"
#include "./../../Entities/TTransform.h"
#include "./../../Entities/TMesh.h"
#include "./../../Entities/TLight.h"
#include "./../../Entities/TCamera.h"

class SceneManager;

class TFNode{
	friend class SceneManager;

public:
	void SetTranslate(toe::core::vector3df translation);	// Sets the rotation of the Node
	void SetRotation(toe::core::vector3df rotation);		// Sets the position of the Node

	void Translate(toe::core::vector3df translation);		// Adds the position to the current position
	void Rotate(toe::core::vector3df rotation);			// Adds the rotation to the current rotation

	toe::core::vector3df GetTranslate();					// Returns the rotation of the Node
	toe::core::vector3df GetRotation();					// Returns the position of the Node

protected:
	TNode* m_entityNode;
	TNode* m_rotationNode;
	TNode* m_positionNode;

	TFNode();
	virtual ~TFNode();
	virtual void CreateEstructure() = 0;		// Rotacion Escala Translacion
	void Attach(TNode* root);					// Node to be attached to

};

#endif