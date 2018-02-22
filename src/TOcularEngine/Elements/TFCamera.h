#ifndef TFCAMERA_H
#define TFCAMERA_H

#include "TFNode.h"

class TFCamera: public TFNode{
public:
	TFCamera(
		vector3df position = vector3df(0, 0, 0),
		vector3df rotation = vector3df(0, 0, 0),
		bool perspective = true
	);
	~TFCamera();

	void CreateEstructure();
	
	void SetPerspective();	// Sets the camera to Perspective
	void SetNearFar();		// Sets the Near and Far components of the camera
	void SetLeftRight();	// Sets the Left and Right components
	void SetUpDown();		// Sets the Up and Down components

private:

};

#endif