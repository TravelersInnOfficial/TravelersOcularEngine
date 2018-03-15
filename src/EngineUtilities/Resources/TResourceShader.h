#ifndef TRESOURCESHADER_H
#define TRESOURCESHADER_H
#include "TResource.h"
#include <GL/glew.h>

class TResourceShader: public TResource {

public:
    TResourceShader();
    TResourceShader(std::string name, GLenum shaderType);
    ~TResourceShader();

    /*********************************************
	 * @brief Loads the mesh passed
	 * @param std::string path of the resource
	 *********************************************/
    bool LoadFile();
    GLuint GetShaderGluint();

private:
    GLuint m_shader;
    GLenum m_type;
    GLuint LoadShader();

};

#endif