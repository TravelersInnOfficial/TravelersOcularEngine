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
    /**
     * @brief   - Constructor del programa donde se leen y compilan los shaders
     * 
     * @param   - Mapa de rutas a los shaders con su tipo
     */
    Program(std::map<std::string, GLenum>);

    /**
     * @brief   - Destructor del programa en el que se eliminan los programas
     */
    ~Program();

    /**
     * @brief   - Returns id of the shader
     * 
     * @return  - GLuint - OpenGL ShaderID 
     */
    GLuint GetProgramID();
    
private:
    GLuint m_programID;             // m_programID - Id del programa
    std::vector<GLuint> m_shaders;  // m_shaders - Shaders que utiliza el programa

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