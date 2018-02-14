#ifndef PROGRAM_H
#define PROGRAM_H

#include <ShaderTypes.h>
#include <GL/glew.h>
#include <map>
#include <vector>

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