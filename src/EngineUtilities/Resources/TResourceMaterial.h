#ifndef TRESOURCEMATERIAL_H
#define TRESOURCEMATERIAL_H

/**
 * @brief Material Resource which contains all mesh properties.
 * 
 * @file TResourceMaterial.h
 */

#include "TResource.h"
#include <glm/vec3.hpp>

class TResourceMaterial: public TResource {

public:
    /**
     * @brief   - Constructor de los materiales 
     *              ponemos los valores por defecto
     */
    TResourceMaterial();

    /**
     * @brief   - Constrcutor de los materiales
     *              ponemos los valores por defecto ademas de cargarlo 
     * 
     * @param   - name - nombre del material a cargar 
     */
    TResourceMaterial(std::string name);

    /**
     * @brief   - Destructor del recurso material 
     */
    ~TResourceMaterial();
    
    /**
     * @brief   - Cargamos el material  
     *
     * @return  - Si se ha cargado el juego satisfactoriamente 
     */
    bool LoadFile();

    /**
     * @brief   - Cambia el valor difuso del material 
     * 
     * @param   . color - Nuevo valor a poner 
     */
    void SetColorDifuse(glm::vec3 color);

    /**
     * @brief   - Devuelve la constante difusa del material 
     * 
     * @return  - glm::vec3 - La variable difusa del material 
     */
    glm::vec3 GetColorDifuse();

    /**
     * @brief   - Cambia la componente especular del material 
     * 
     * @param   - color - Nuevo valor  de especular a poner
     */
    void SetColorSpecular(glm::vec3 color);

    /**
     * @brief   - Devuelve la constante especular del material 
     * 
     * @return  - glm::vec3 - La variable especular del material 
     */
    glm::vec3 GetColorSpecular();

    /**
     * @brief   - Cambia la componente ambiente del material 
     * 
     * @param   - color - Nuevo valor de ambiente a poner en el material 
     */
    void SetColorAmbient(glm::vec3 color);

    /**
     * @brief   - Devuelve la componente ambiente del material
     *  
     * @return  - glm::vec3 - La variable ambiente del material
     */
    glm::vec3 GetColorAmbient();

    /**
     * @brief   - Cambia la componente emisiva del material 
     * 
     * @param   - color - Nuevo valor de emision a poner en el material
     */
    void SetColorEmmisive(glm::vec3 color);

    /**
     * @brief   - Devuelve la componente de emision del material 
     * 
     * @return  - glm::vec3 - La variable de emision del material 
     */
    glm::vec3 GetColorEmmisive();

    /**
     * @brief   - Cambia la componente de transparencia del material 
     * 
     * @param   - color - Nuevo valor de transparencia a poner en el material 
     */
    void SetColorTransparent(glm::vec3 color);

    /**
     * @brief   - Devuelve la componente de transparencia del material 
     * 
     * @return  - glm::vec3 - La variable de transparencia del material
     */
    glm::vec3 GetColorTransparent();


    void SetTwoSided(int value);
    int GetTwoSided();

    void SetShadingMode(int value);
    int GetShadingMode();

    void SetBlendFunc(int value);
    int GetBlendFunc();

    /**
     * @brief   - Cambia la componente de opacidad del material 
     * 
     * @param   - value - la componente de opacidad del material 
     */
    void SetOpacity(float value);
    
    /**
     * @brief   - Devuelve la componente de opacidad del material 
     * 
     * @return  - glm::vec3 - La variable de opacidad del material 
     */
    float GetOpacity();

    /**
     * @brief   - Cambia la componente de brillo del material 
     * 
     * @param   - value - la componente de brillo del material 
     */    
    void SetShininess(float value);
    
    /**
     * @brief   - Devuelve la componente de brillo del material 
     * 
     * @return  - float - La variable de brillo del material 
     */
    float GetShininess();

    /**
     * @brief   - Cambia la componente de fuerza del brillo del material 
     * 
     * @param   - value - la componente de fuerza del brillo del material 
     */        
    void SetShininessStrength(float value);
    
    /**
     * @brief   - Devuelve la componente de fuerza del brillo del material 
     * 
     * @return  - float - La variable de fuerza del brillo del material 
     */
    float GetShininessStrength();

    /**
     * @brief   - Cambia la componente de refracción del material 
     * 
     * @param   - value - la componente de refracción del material 
     */              
    void SetReflact(float value);
    
    /**
     * @brief   - Devuelve la componente de refracción del material 
     * 
     * @return  - float - La variable de refracción del material 
     */
    float GetReflact();

private:
	glm::vec3 	m_colorDifuse;          // m_colorDifuse - Componente difusa del material
	glm::vec3 	m_colorSpecular;        // m_colorSpecular - Componente especular del material
	glm::vec3 	m_colorAmbient;         // m_colorAmbient - Componente ambiente del material
	glm::vec3 	m_colorEmmisive;        // m_colorEmmisive - Componente emisiva del material
	glm::vec3 	m_colorTransparent;     // m_colorTRansparent - Componente transparente del material

	int 		m_twosided;
	int 		m_shadingModel;
	int 		m_blendFunc;
	
	float 		m_opacity;             // m_opacity - Componente de opacidad del material
	float 		m_shininess;           // m_shininess - Brillo del material
	float 		m_shininessStrength;   // m_shininessStrenght - Fuerza del brillo del material
	float 		m_reflact;             // m_reflact - Refraccion del material
};

#endif