#ifndef TFCAMERA_H
#define TFCAMERA_H

/**
 * @brief Camera Entity Facade.
 * 
 * @file TFCamera.h
 */

#include "TFNode.h"

class TFCamera: public TFNode{
	friend class SceneManager;

public:
	void SetRotation(TOEvector3df rotation) override; 		// Sets the position of the Node
	void Rotate(TOEvector3df rotation) override; 			// Adds the rotation to the current rotation
	/**
	 * @brief Set the Rotation Locked
	 * 
	 * @param locked: lock rotation or not
	 */
	void SetRotationLocked(bool locked);

	void SetPerspective(bool perspectiveCamera);	// Sets the camera to Perspective
	void SetNearFar(float near, float far);			// Sets the Near and Far components of the camera
	void SetLeftRight(float left, float right);		// Sets the Left and Right components
	void SetTopBottom(float up, float down);		// Sets the Up and Down components
	void LookAt(TOEvector3df target, TOEvector3df up = TOEvector3df(0,1,0));

	bool GetPerspective();							// Gets the Perspective data from the Camera
	float GetNear();								// Gets the Near data from the Camera
	float GetFar();									// Gets the Far data from the Camera
	float GetLeft();								// Gets the Left data from the Camera
	float GetRight();								// Gets the Right data from the Camera
	float GetTop();									// Gets the Up data from the Camera
	float GetBottom();								// Gets the Down data from the Camera

protected:
	TFCamera(
		TOEvector3df position = TOEvector3df(0, 0, 0),
		TOEvector3df rotation = TOEvector3df(0, 0, 0),
		bool perspective = true
	);
	~TFCamera();

	bool m_RotationLocked;	
};

#endif