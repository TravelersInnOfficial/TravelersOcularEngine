#ifndef TFMESH_H
#define TFMESH_H

#include "./../../TNode.h"

class TFMesh{
public:
	TFMesh();
	~TFMesh();

	void SetPosition();	// Sets the rotation of the Node
	void SetRotation();	// Sets the position of the Node
	void SetScale();	// Sets the scale of the Node
	
	void Move();		// Adds the position to the current position
	void Rotate();		// Adds the rotation to the current rotation
	void Scale();		// Adds the scale to the current scale

private:
	TNode* meshNode;
	TNode* rotationNode;
	TNode* positionNode;
	TNode* scaleNode;

};

#endif