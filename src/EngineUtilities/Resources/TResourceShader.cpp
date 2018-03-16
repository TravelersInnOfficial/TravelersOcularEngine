#include "TResourceShader.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

TResourceShader::TResourceShader(std::string name, GLenum shaderType){
	m_name = name;
	m_type = shaderType;
	m_shader = 0;
	LoadFile();
}

TResourceShader::TResourceShader(){
}

TResourceShader::~TResourceShader(){

}

GLuint TResourceShader::GetShaderGluint(){
	return m_shader;
}

bool TResourceShader::LoadFile(){
	bool toRet = false;
	m_shader = LoadShader();
	SetLoaded(toRet);
	return toRet;
}

GLuint TResourceShader::LoadShader(){
    // Read shader from file
    std::ifstream in(m_name);
    std::string src = "";
    std::string line = "";
    while(std::getline(in,line)) src += line + "\n";

    const char* source = src.c_str();

	//GLint compiled;
    GLuint shaderID = glCreateShader(m_type);
    glShaderSource(shaderID,1,&source,nullptr);
    glCompileShader(shaderID);
    
	if(!shaderID){
        std::cerr << "Could not compile the shader"<<std::endl;
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
        
        std::cout << msg << std::endl;        
	}

    return shaderID;
}