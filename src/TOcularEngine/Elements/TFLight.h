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
#include <TOEvector3d.h>
#include "TFNode.h"

class TFLight: public TFNode{
	friend class SceneManager;
	friend class TFRoom;

public:
	void SetColor(TOEvector4df color);				// Changes the light color
	void SetAttenuation(float attenuation);			// Changes the light attenuation
	void SetActive(bool active);					// Changes the light active state
	void SetDirectional(bool directional);			// Changes the light type

	TOEvector4df GetColor();						// Returns the light color
	float GetAttenuation();							// Returns the light attenuation
	bool GetActive();								// Returns the light active state
	bool GetDirectional();							// Returns the light type
	glm::vec3 CalculateLocation();

	void SetBoundBox(bool) override;				// Shows or hide tmesh bounding box
	void SetDirection(TOEvector3df direction);
	TOEvector3df GetDirection();

	void SetShadowsState(bool shadowState);
	bool GetShadowsState();

	bool CalculateShadowTexture(int num);
	
private:
	TFLight(
		TOEvector3df position = TOEvector3df(0, 0, 0),
		TOEvector3df rotation = TOEvector3df(0, 0, 0),
		TOEvector4df color = TOEvector4df(255.0f, 255.0f, 255.0f, 255.0f),
		float attenuation = 0.0f
	);
	~TFLight();

	void DrawLight(int num);
	void DrawLightShadow(int num);

	void InitShadow();
	void EraseShadow();

	glm::vec3 m_LastLocation;

	GLuint m_fbo;
    GLuint m_shadowMap;
	glm::mat4 m_depthWVP;

};

#endif