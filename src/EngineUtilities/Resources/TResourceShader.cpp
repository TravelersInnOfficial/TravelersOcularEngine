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
	bool toRet = false;
	
	SetLoaded(toRet);
	return toRet;
}