#include "TResourceShader.h"

TResourceShader::TResourceShader(std::string name){
	m_name = name;
	LoadFile();
}

TResourceShader::TResourceShader(){

}

TResourceShader::~TResourceShader(){

}

bool TResourceShader::LoadFile(){
	return false;
}

bool TResourceShader::LoadFile(std::string name){
	SetName(name);
	return false;
}