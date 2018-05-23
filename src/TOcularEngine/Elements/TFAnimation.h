#ifndef TFANIMATION_H
#define TFANIMATION_H

/**
 * @brief Animation Entity Facade.
 * 
 * @file TFAnimation.h
 */

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
	void SetAnimationPaths(std::string ID, const std::vector<std::string> &paths, int fps = 25);
	
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

	/**
	 * @brief Play another animation and queue last animation
	 * 
	 * @param ID: name of the animation
	 * @param fps: speed of animation
	 */
	void PlayAnimation(std::string ID, int fps = 25);

	/**
	 * @brief Play another animation and queue last animation
	 * 
	 * @param ID: name of the animation
	 * @param fps: speed of animation
	 */
	void PlayAnimationAbove(std::string ID, int fps = 25);

	/**
	 * @brief After playing an animation, this will take the time from the sync one
	 * 
	 * @param master 
	 */
	void BindSyncAnimation(TFAnimation* master);

	/**
	 * @brief Get Actual Animation Frame
	 * 
	 * @return int: frame
	 */
	int GetAnimationFrame();

	/**
	 * @brief Gets playing animation name
	 * 
	 * @return std::string: name
	 */
	std::string GetAnimationName();


protected:
	TFAnimation(
		TOEvector3df position = TOEvector3df(0, 0, 0),
		TOEvector3df rotation = TOEvector3df(0, 0, 0),
		TOEvector3df scale = TOEvector3df(1, 1, 1)
	);
	~TFAnimation();
    
};

#endif