#ifndef TFDOME_H
#define TFDOME_H

/**
 * @brief Dome Entity Facade.
 * 
 * @file TFDome.h
 */

#include "TFNode.h"

class TFDome: public TFNode{
	friend class SceneManager;
public:
    
    void SetTexture(std::string texturePath = "");		// Replaces the Texture with a new one

private:
	TFDome(
		TOEvector3df position = TOEvector3df(0, 0, 0),
		TOEvector3df rotation = TOEvector3df(0, 0, 0),
		TOEvector3df scale = TOEvector3df(1.0f, 1.0f, 1.0f),
		std::string texturePath = ""
	);
	~TFDome();

};

#endif