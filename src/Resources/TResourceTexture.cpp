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
	bool toRet = false;
	
	SetLoaded(toRet);
	return toRet;
}