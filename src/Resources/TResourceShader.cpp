#include "TResourceShader.h"

TResourceShader::TResourceShader(std::string name){
	m_name = name;
	LoadFile();
}

TResourceShader::~TResourceShader(){}

bool TResourceShader::LoadFile(){
	return false;
}