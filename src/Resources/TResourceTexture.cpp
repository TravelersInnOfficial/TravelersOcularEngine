#include "TResourceTexture.h"

TResourceTexture::TResourceTexture(std::string name){
	m_name = name;
	LoadFile();
}

TResourceTexture::TResourceTexture(){
	
}

TResourceTexture::~TResourceTexture(){

}

bool TResourceTexture::LoadFile(){
	toRet = false;
	
	SetLoaded(toRet);
	return toRet;
}

bool TResourceTexture::LoadFile(std::string name){
	toRet = false;
	SetName(name);
	
	SetLoaded(toRet);
	return toRet;
}