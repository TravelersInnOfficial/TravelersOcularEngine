#ifndef TFANIMATION_H
#define TFANIMATION_H

#include "TFNode.h"

class TFAnimation: public TFNode{
	friend class SceneManager;

public:
	void SetAnimationPaths(int frames, std::string paths[]);        // Sets all paths for all the meshes and number of frames
	void SetTexture(std::string texturePath = "");		// Replaces the Texture with a new one
    void SetInvisible();								// Assigns and invisible texture (0,0,0,0)
	void SetBoundBox(bool visible) override;			// Shows or hide mesh bounding box
   
    void Update(float deltatime);

protected:
	TFAnimation(
		toe::core::TOEvector3df position = toe::core::TOEvector3df(0, 0, 0),
		toe::core::TOEvector3df rotation = toe::core::TOEvector3df(0, 0, 0),
		toe::core::TOEvector3df scale = toe::core::TOEvector3df(1, 1, 1)
	);
	~TFAnimation();
    
};

#endif