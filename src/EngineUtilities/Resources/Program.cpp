#include "Program.h"
#include "./../TResourceManager.h"
// All needed except iostream for debugging
#include <iostream>
#include <fstream>
#include <stdexcept>

// Glew for opengl
#include <GL/glew.h>

Program::Program(std::map<std::string, GLenum> shaderData){
    // Load all the shaders    
    m_shaders = std::vector<GLuint>(shaderData.size());
    
    // Iterate all shaders
    std::map<std::string, GLenum>::iterator it;
    int i;
    for(it = shaderData.begin(), i = 0; it != shaderData.end(); it++, i++){
        m_shaders[i] = LoadShader(it->first, it->second);
    }

    // Creamos el programa y le añadimos los shaders
    m_programID = glCreateProgram();

    // Fijar todos los shaders
    for(i = 0; i < m_shaders.size(); i++){
        glAttachShader(m_programID, m_shaders[i]);
    }

    // Se linkea el programa a los shaders
    glLinkProgram(m_programID);

    // Defijar los shaders una vez unidos
    for(i = 0; i < m_shaders.size(); i++){
        glDetachShader(m_programID, m_shaders[i]);
    }

    // SE COMPRUEBA SI LINKEA BIEN
    GLint status;
    glGetProgramiv(m_programID, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        std::string msg("Program linking failure: ");

        GLint infoLogLength;
        glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
        char* strInfoLog = new char[infoLogLength + 1];
        glGetProgramInfoLog(m_programID, infoLogLength, nullptr, strInfoLog);
        msg += strInfoLog;
        delete[] strInfoLog;

        glDeleteProgram(m_programID); m_programID = 0;
        
        //throw std::runtime_error(msg);
        std::cout << msg << std::endl;
    }
}

// Delete all shaders
Program::~Program(){
    for(int i = 0; i < m_shaders.size(); i++) glDeleteShader(m_shaders[i]);
    glDeleteProgram(m_programID);
}


GLuint Program::LoadShader(std::string shaderPath, GLenum shaderType){
    TResourceManager* rm = TResourceManager::GetInstance();
    TResourceShader* rs = rm->GetResourceShader(shaderPath, shaderType);
    GLuint toRet = 0;
    if(rs != nullptr) toRet = rs->GetShaderGluint();
    return toRet;
}

GLuint Program::GetProgramID(){
    return m_programID;
}