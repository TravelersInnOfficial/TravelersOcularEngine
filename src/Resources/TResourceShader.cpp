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
	toRet = false;
	
	SetLoaded(toRet);
	return toRet;
}

bool TResourceShader::LoadFile(std::string name){
	toRet = false;
	SetName(name);
	
	SetLoaded(toRet);
	return toRet;
}