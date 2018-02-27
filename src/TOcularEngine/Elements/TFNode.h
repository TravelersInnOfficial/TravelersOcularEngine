#ifndef TFNODE_H
#define TFNODE_H

#include <TOEvector3d.h>
#include <TColor.h>
#include <glm/gtx/matrix_decompose.hpp>
#include "./../../EngineUtilities/TNode.h"
#include "./../../EngineUtilities/Entities/TTransform.h"
#include "./../../EngineUtilities/Entities/TMesh.h"
#include "./../../EngineUtilities/Entities/TLight.h"
#include "./../../EngineUtilities/Entities/TCamera.h"

class SceneManager;

class TFNode{
	friend class SceneManager;

public:
	void SetTranslate(toe::core::TOEvector3df translation);	// Sets the rotation of the Node
	void SetRotation(toe::core::TOEvector3df rotation);		// Sets the position of the Node

	void Translate(toe::core::TOEvector3df translation);		// Adds the position to the current position
	void Rotate(toe::core::TOEvector3df rotation);				// Adds the rotation to the current rotation

	toe::core::TOEvector3df GetTranslation();					// Returns the rotation of the Node
	toe::core::TOEvector3df GetRotation();						// Returns the position of the Node

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