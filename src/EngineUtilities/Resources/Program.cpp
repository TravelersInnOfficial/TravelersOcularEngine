#include "Program.h"
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

	// No es necesario porque no se escribe en mas de un buffer
	//glBindFragDataLocation(m_programID, 0, "outColor");
	// insert location binding code here
	//glBindAttribLocation(m_programID, 0, "position");
	//glBindAttribLocation(m_programID, 1, "vertexColor");

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

Program::~Program(){
    // Delete all shaders
    for(int i = 0; i < m_shaders.size(); i++){
        glDeleteShader(m_shaders[i]);
    }
    glDeleteProgram(m_programID);
}


GLuint Program::LoadShader(std::string shaderPath, GLenum shaderType){
    // Read shader from file
    std::ifstream in(shaderPath);
    std::string src = "";
    std::string line = "";
    while(std::getline(in,line)) src += line + "\n";
    //std::cout << src;
    
    const char* source = src.c_str();

	//GLint compiled;
    GLuint shaderID = glCreateShader(shaderType);
    glShaderSource(shaderID,1,&source,nullptr);
    glCompileShader(shaderID);
    
	if(!shaderID){
        std::cerr << "Could not compile the shader";
        return 0;
    }

    // Check compile status
    GLint status;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE){
		std::string msg("Compile failure in shader:\n");

        GLint infoLogLength;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
        char* strInfoLog = new char[infoLogLength + 1];
        glGetShaderInfoLog(shaderID, infoLogLength, nullptr, strInfoLog);
        msg += strInfoLog;
        delete[] strInfoLog;

        glDeleteShader(shaderID); shaderID = 0;
        //throw std::runtime_error(msg);
        std::cout << msg << std::endl;        
	}

    return shaderID;
}

GLuint Program::GetProgramID(){
    return m_programID;
}