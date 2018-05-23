#ifndef TFLIGHT_H
#define TFLIGHT_H

/**
 * @brief Light Entity Facade.
 * 
 * @file TFLight.h
 * 
 *  Shadows bassed in #16 opengl tutorial
 * 	http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-16-shadow-mapping/#rendering-the-shadow-map
 */

#include <TOEvector4d.h>
#include <TOEvector3d.h>
#include "TFNode.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class TFLight: public TFNode{
	friend class SceneManager;
	friend class TFRoom;

public:

	/**
	 * @brief Changes the light color
	 * 
	 * @param color: light color
	 */
	void SetColor(TOEvector4df color);
	
	/**
	 * @brief Changes the light attenuation
	 * 
	 * @param attenuation: light range
	 */
	void SetAttenuation(float attenuation);
	
	/**
	 * @brief Changes the light active state
	 * 
	 * @param active: true = actived
	 */
	void SetActive(bool active);
	
	/**
	 * @brief Changes the light type
	 * 
	 * @param directional: true = directional 
	 */
	void SetDirectional(bool directional);


	/**
	 * @brief Returns the light color
	 * 
	 * @return TOEvector4df: rbga color
	 */
	TOEvector4df GetColor();
	
	/**
	 * @brief Returns the light attenuation
	 * 
	 * @return float: range
	 */
	float GetAttenuation();
	
	/**
	 * @brief Returns the light active state
	 * 
	 * @return true: Light enabled
	 * @return false: Light disabled
	 */
	bool GetActive();
	
	/**
	 * @brief Returns the light type
	 * 
	 * @return true: directional light 
	 * @return false: point light
	 */
	bool GetDirectional();

	/**
	 * @brief Returns the light position
	 * 
	 * @return glm::vec3: position
	 */
	glm::vec3 CalculateLocation();

	/**
	 * @brief Set visibility of Bound Box
	 * 
	 */
	void SetBoundBox(bool) override;				// Shows or hide tmesh bounding box


	/**
	 * @brief Set the Direction
	 * 
	 * @param direction: light direction
	 */
	void SetDirection(TOEvector3df direction);

	/**
	 * @brief Get the Direction
	 * 
	 * @return TOEvector3df: light direction
	 */
	TOEvector3df GetDirection();


	/**
	 * @brief Set the Shadows State
	 * 
	 * @param shadowState: set if emmits shadows or not
	 */
	void SetShadowsState(bool shadowState);
	
	/**
	 * @brief Get the Shadows State
	 * 
	 * @return true 
	 * @return false 
	 */
	bool GetShadowsState();

	/**
	 * @brief Calculates Shadow Textures
	 * 
	 * @param num 
	 * @return true 
	 * @return false 
	 */
	bool CalculateShadowTexture(int num);
	
private:

	/**
	 * @brief Construct a new TFLight object
	 * 
	 * @param position 
	 * @param rotation 
	 * @param color 
	 * @param attenuation: range of attenuation (0 infinite)
	 */
	TFLight(
		TOEvector3df position = TOEvector3df(0, 0, 0),
		TOEvector3df rotation = TOEvector3df(0, 0, 0),
		TOEvector4df color = TOEvector4df(255.0f, 255.0f, 255.0f, 255.0f),
		float attenuation = 0.0f
	);
	
	/**
	 * @brief Destroy the TFLight object
	 * 
	 */
	~TFLight();

	/**
	 * @brief Sends Shader light info
	 * 
	 * @param num 
	 */
	void DrawLight(int num);
	
	/**
	 * @brief Gets Light Shadow projection matrix
	 * 
	 * @param num 
	 */
	void DrawLightShadow(int num);
	
	/**
	 * @brief Sends Shader shadows light info
	 * 
	 * @param num 
	 */
	void DrawLightMVP(int num);

	/**
	 * @brief Init Shadows frame buffer
	 * 
	 */
	void InitShadow();

	/**
	 * @brief Removes shadow
	 * 
	 */
	void EraseShadow();

	glm::vec3 m_LastLocation;			// Last position of the light

	GLuint m_fbo;						// Frame buffer to render texture
    unsigned int m_shadowMap;			// Shadow texture
	glm::mat4 m_depthWVP;				// Light view matrix

};

#endif