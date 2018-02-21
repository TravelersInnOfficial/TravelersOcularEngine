#ifndef TFCAMERA_H
#define TFCAMERA_H

#include "TFNode.h"

class TFCamera: public TFNode{
public:
	TFCamera(bool perspective);
	~TFCamera();
	
	void SetPerspective();	// Sets the camera to Perspective
	void SetNearFar();		// Sets the Near and Far components of the camera
	void SetLeftRight();	// Sets the Left and Right components
	void SetUpDown();		// Sets the Up and Down components

private:

};

#endif