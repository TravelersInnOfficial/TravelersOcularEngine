#ifndef TFCAMERA_H
#define TFCAMERA_H

#include "TFNode.h"

class TFCamera: public TFNode{
	friend class SceneManager;

public:
	void SetPerspective(bool perspectiveCamera);	// Sets the camera to Perspective
	void SetNearFar(float near, float far);			// Sets the Near and Far components of the camera
	void SetLeftRight(float left, float right);		// Sets the Left and Right components
	void SetTopBottom(float up, float down);		// Sets the Up and Down components

	bool GetPerspective();							// Gets the Perspective data from the Camera
	float GetNear();								// Gets the Near data from the Camera
	float GetFar();									// Gets the Far data from the Camera
	float GetLeft();								// Gets the Left data from the Camera
	float GetRight();								// Gets the Right data from the Camera
	float GetTop();									// Gets the Up data from the Camera
	float GetBottom();								// Gets the Down data from the Camera

private:
	TFCamera(
		vector3df position = vector3df(0, 0, 0),
		vector3df rotation = vector3df(0, 0, 0),
		bool perspective = true
	);
	~TFCamera();
	void CreateEstructure();

};

#endif