#ifndef TFNODE_H
#define TFNODE_H

#include <vector3d.h>
#include "./../../TNode.h"

class TFNode{
public:
	TFNode(vector3df position = vector3df(0, 0, 0), vector3df rotation = vector3df(0, 0, 0));
	~TFNode();

	void SetTranslate();	// Sets the rotation of the Node
	void SetRotation();		// Sets the position of the Node

	void Translate();		// Adds the position to the current position
	void Rotate();			// Adds the rotation to the current rotation

private:
	TNode* m_meshNode;
	TNode* m_rotationNode;
	TNode* m_positionNode;

};

#endif