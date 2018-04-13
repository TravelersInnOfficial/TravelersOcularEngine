#ifndef TFANIMATION_H
#define TFANIMATION_H

#include "TFNode.h"

class TFAnimation: public TFNode{
	friend class SceneManager;

public:
	/**
	 * @brief Replaces the Texture with a new one
	 * 
	 * @param texturePath: path to texture from executable
	 */
	void SetTexture(std::string texturePath = "");
    /**
     * @brief Assigns and invisible texture (0,0,0,0)
     * 
     */
	void SetInvisible();
	/**
	 * @brief Shows or hide mesh bounding box
	 * 
	 * @param visible: visibility of bounding box
	 */
	void SetBoundBox(bool visible) override;
	
	/**
	 * @brief Sets all paths for all the meshes and number of frames
	 * 
	 * @param ID 
	 * @param frames 
	 * @param paths 
	 */
	void SetAnimationPaths(std::string ID, int frames, std::string paths[], int fps = 25);
	/**
	 * @brief Update animation frames
	 * 
	 * @param deltatime 
	 */
    void Update(float deltatime);

	/**
	 * @brief Play another animation
	 * 
	 * @param ID: name of the animation
	 * @param fps 
	 */
    void ChangeAnimation(std::string ID, int fps = 25);

protected:
	TFAnimation(
		toe::core::TOEvector3df position = toe::core::TOEvector3df(0, 0, 0),
		toe::core::TOEvector3df rotation = toe::core::TOEvector3df(0, 0, 0),
		toe::core::TOEvector3df scale = toe::core::TOEvector3df(1, 1, 1)
	);
	~TFAnimation();
    
};

#endif