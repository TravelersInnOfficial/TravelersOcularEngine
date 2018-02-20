#ifndef TFCAMERA_H
#define TFCAMERA_H

#include "./../../TNode.h"

class TFCamera{
public:
	TFCamera();
	~TFCamera();

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