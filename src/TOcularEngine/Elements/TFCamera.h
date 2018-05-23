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
	/**
	 * @brief Sets the position of the Node
	 * 
	 * @param rotation: camera rotation
	 */
	void SetRotation(TOEvector3df rotation) override;
	
	/**
	 * @brief Adds the rotation to the current rotation
	 * 
	 * @param rotation: camera rotation
	 */
	void Rotate(TOEvector3df rotation) override;
	
	/**
	 * @brief Set the Rotation Locked
	 * 
	 * @param locked: lock rotation or not
	 */
	void SetRotationLocked(bool locked);

	/**
	 * @brief Sets the camera to Perspective
	 * 
	 * @param perspectiveCamera: true = perspective / false = orthogonal
	 */
	void SetPerspective(bool perspectiveCamera);
	
	/**
	 * @brief Sets the Near and Far components of the camera
	 * 
	 * @param near: near distance of clip plane
	 * @param far: far distance of clip plane
	 */
	void SetNearFar(float near, float far);

	/**
	 * @brief Sets the Left and Right components
	 * 
	 * @param left: left distance of clip plane
	 * @param right: right distance of clip plane
	 */
	void SetLeftRight(float left, float right);

	/**
	 * @brief Sets the Up and Down components
	 * 
	 * @param up: up distance of clip plane
	 * @param down: down distance of clip plane
	 */
	void SetTopBottom(float up, float down);
	

	/**
	 * @brief Sets camera rotation to point Target.
	 * 
	 * @param target: target to look at
	 * @param up: Up vector
	 */
	void LookAt(TOEvector3df target, TOEvector3df up = TOEvector3df(0,1,0));

	/**
	 * @brief Get the Perspective Data from the camera
	 * 
	 * @return true: perpective
	 * @return false: orthogonal
	 */
	bool GetPerspective();
	
	/**
	 * @brief Get the Near Data from the camera
	 * 
	 * @return float: near clip distance
	 */
	float GetNear();
	
	/**
	 * @brief Get the Far Data from the camera
	 * 
	 * @return float: far clip distance
	 */
	float GetFar();
	
	/**
	 * @brief Get the Left Data from the camera
	 * 
	 * @return float: left clip distance
	 */
	float GetLeft();
	
	/**
	 * @brief Get the Right Data from the camera
	 * 
	 * @return float: right clip distance
	 */
	float GetRight();
	
	/**
	 * @brief Get the Top Data from the camera
	 * 
	 * @return float: top clip distance
	 */
	float GetTop();
	
	/**
	 * @brief Get the Bottom Data from the camera
	 * 
	 * @return float: bottom clip distance
	 */
	float GetBottom();

protected:

	/**
	 * @brief Construct a new Camera Internally and returns Facade
	 * 
	 * @param position: position
	 * @param rotation: rotation
	 * @param perspective: true = perspective / false = orthogonal
	 */
	TFCamera(
		TOEvector3df position = TOEvector3df(0, 0, 0),
		TOEvector3df rotation = TOEvector3df(0, 0, 0),
		bool perspective = true
	);

	/**
	 * @brief Destroy the Camera
	 * 
	 */
	~TFCamera();

	bool m_RotationLocked; // Check if has locked rotation
};

#endif