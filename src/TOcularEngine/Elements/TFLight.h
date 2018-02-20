#ifndef TFLIGHT_H
#define TFLIGHT_H

#include "./../../TNode.h"

class TFLight{
public:
	TFLight();
	~TFLight();

	void SetPosition();	// Sets the rotation of the Node
	void SetRotation();	// Sets the position of the Node
	
	void Move();		// Adds the position to the current position
	void Rotate();		// Adds the rotation to the current rotation

private:
	TNode* meshNode;
	TNode* rotationNode;
	TNode* positionNode;

};

#endif