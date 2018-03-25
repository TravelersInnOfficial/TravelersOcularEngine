#ifndef TFLIGHT_H
#define TFLIGHT_H

/**
 * @brief 
 * 
 * @file TFLight.h
 * @author Travelers INN
 * @date 2018-03-20
 * 
 *  Shadows bassed in #16 opengl tutorial 
 * 	http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-16-shadow-mapping/#rendering-the-shadow-map
 */

#include <TOEvector4d.h>
#include "TFNode.h"

class TFLight: public TFNode{
	friend class SceneManager;

public:
	void SetColor(toe::core::TOEvector4df color);	// Changes the light color
	void SetAttenuation(float attenuation);			// Changes the light attenuation
	void SetActive(bool active);					// Changes the light active state

	toe::core::TOEvector4df GetColor();				// Returns the light color
	float GetAttenuation();							// Returns the light attenuation
	bool GetActive();								// Returns the light active state
	glm::vec3 CalculateLocation();

	void SetBoundBox(bool);
	
private:
	TFLight(
		toe::core::TOEvector3df position = toe::core::TOEvector3df(0, 0, 0),
		toe::core::TOEvector3df rotation = toe::core::TOEvector3df(0, 0, 0),
		toe::core::TOEvector4df color = toe::core::TOEvector4df(255.0f, 255.0f, 255.0f, 255.0f),
		float attenuation = 0.0f
	);
	~TFLight();
	void DrawLight(int num);
	void DrawLightShadow(int num);
	glm::vec3 m_LastLocation;

};

#endif