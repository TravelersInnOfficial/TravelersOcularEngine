#ifndef TRESOURCESHADER_H
#define TRESOURCESHADER_H

/**
 * @brief Shader Resource containing Shader ID. 
 * 
 * @file TResourceShader.h
 */

#include "TResource.h"
#include <GL/glew.h>

class TResourceShader: public TResource {

public:
    /**
     * @brief   - Constructor del shader en el que inicializamos las variables y lo cargamos 
     * 
     * @param   - name - Ruta del shader 
     * @param   - shaderType - Enumerador con el tipo de shader que vamos a crear 
     */
    TResourceShader(std::string name, GLenum shaderType);

    /**
     * @brief   - Destructor del shader 
     */
    ~TResourceShader();

    /*********************************************
	 * @brief Loads the shader passed
	 * @param std::string path of the resource
	 *********************************************/
    bool LoadFile();

    /**
     * @brief   - Devolvemos un puntero al shader ya compilado 
     *
     * @return  - GLuint - PUntero al shader ya compilado
     */
    GLuint GetShaderGluint();

private:
    GLuint m_shader;    // m_shader - Puntero al shader
    GLenum m_type;      // m_type - Tipo de shader

    /**
     * @brief   - Cargamos el shader, y lo compilamos 
     *
     * @return  - GLuint - Puntero al shader 
     */
    GLuint LoadShader();

};

#endif