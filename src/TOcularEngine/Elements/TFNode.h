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
	void SetTranslate(toe::core::TOEvector3df translation);		// Sets the rotation of the Node
	void SetRotation(toe::core::TOEvector3df rotation);			// Sets the position of the Node
	void SetScale(toe::core::TOEvector3df scale);				// Sets the scale of the Node

	void Translate(toe::core::TOEvector3df translation);		// Adds the position to the current position
	void Rotate(toe::core::TOEvector3df rotation);				// Adds the rotation to the current rotation
	void Scale(toe::core::TOEvector3df scale);					// Adds the scale to the current scale

	toe::core::TOEvector3df GetTranslation();	// Returns the rotation of the Node
	toe::core::TOEvector3df GetRotation();		// Returns the position of the Node
	toe::core::TOEvector3df GetScale();			// Returns the scale of the Node

	void AddChild(TFNode* children);			// Adds a Children to the TFNode
	void RemoveChild(TFNode* children);			// Removes Children from the TFNode
	void SetParent(TFNode* parent = nullptr);	// Adds a Parent to the TFNode
	void RemoveParent();						// Removes Parent from the TFNode

	TFNode* GetParent();
	std::vector<TFNode*> GetChildren();

protected:
	TNode* m_entityNode;
	TNode* m_positionNode;
	TNode* m_rotationNode;
	TNode* m_scaleNode;
	
	std::vector<TFNode*> m_children;
	TFNode* m_parent;				// If Parent is null, this TFNode is attatched to the ROOT NODE

	TFNode();
	virtual ~TFNode();
	void DeleteChildren();
	void Attach(TNode* root);	// TNode to be attached to (Rotation will be children to the new TNode)	

};

#endif