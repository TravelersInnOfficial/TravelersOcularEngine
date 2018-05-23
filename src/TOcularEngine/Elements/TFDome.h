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
    
	/**
	 * @brief Set SkyDome Texture
	 * 
	 * @param texturePath 
	 */
    void SetTexture(std::string texturePath = "");		// Replaces the Texture with a new one

private:
	/**
	 * @brief Construct a new SkyDome
	 * 
	 * @param position 
	 * @param rotation 
	 * @param scale 
	 * @param texturePath 
	 */
	TFDome(
		TOEvector3df position = TOEvector3df(0, 0, 0),
		TOEvector3df rotation = TOEvector3df(0, 0, 0),
		TOEvector3df scale = TOEvector3df(1.0f, 1.0f, 1.0f),
		std::string texturePath = ""
	);

	/**
	 * @brief Destroy the SkyBox
	 * 
	 */
	~TFDome();

};

#endif