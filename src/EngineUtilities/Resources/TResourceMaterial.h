#ifndef TRESOURCEMATERIAL_H
#define TRESOURCEMATERIAL_H

#include "TResource.h"
#include <glm/vec3.hpp>

class TResourceMaterial: public TResource {

public:
    TResourceMaterial();
    TResourceMaterial(std::string name);
    ~TResourceMaterial();
    
    /*********************************************
	 * @brief Loads the mesh passed
	 * @param std::string path of the resource
	 *********************************************/
    bool LoadFile();

    void SetColorDifuse(glm::vec3 color);
    glm::vec3 GetColorDifuse();

    void SetColorSpecular(glm::vec3 color);
    glm::vec3 GetColorSpecular();

    void SetColorAmbient(glm::vec3 color);
    glm::vec3 GetColorAmbient();

    void SetColorEmmisive(glm::vec3 color);
    glm::vec3 GetColorEmmisive();

    void SetColorTransparent(glm::vec3 color);
    glm::vec3 GetColorTransparent();

    void SetTwoSided(int value);
    int GetTwoSided();

    void SetShadingMode(int value);
    int GetShadingMode();

    void SetBlendFunc(int value);
    int GetBlendFunc();

    void SetOpacity(float value);
    float GetOpacity();

    void SetShininess(float value);
    float GetShininess();

    void SetShininessStrength(float value);
    float GetShininessStrength();
    
    void SetReflact(float value);
    float GetReflact();

private:
	glm::vec3 	m_colorDifuse;
	glm::vec3 	m_colorSpecular;
	glm::vec3 	m_colorAmbient;
	glm::vec3 	m_colorEmmisive;
	glm::vec3 	m_colorTransparent;

	int 		m_twosided;
	int 		m_shadingModel;
	int 		m_blendFunc;
	
	float 		m_opacity;
	float 		m_shininess;
	float 		m_shininessStrength;
	float 		m_reflact;
};

#endif