#ifndef PROGRAM_H
#define PROGRAM_H

#include <ShaderTypes.h>
#include <map>
#include <vector>
#include <string>

typedef unsigned int GLuint;
typedef unsigned int GLenum;

class Program{

public:
    Program(std::map<std::string, GLenum>);
    ~Program();

    /**
     * @brief Returns id of the shader
     * 
     * @return GLuint: OpenGL ShaderID 
     */
    GLuint GetProgramID();
    
private:
    GLuint m_programID;
    std::vector<GLuint> m_shaders;

    /**
     * @brief Creates shaders depending of type
     * 
     * @param shaderPath 
     * @param shaderType 
     * @return GLuint 
     */
    GLuint LoadShader(std::string shaderPath, GLenum shaderType);
};

#endif