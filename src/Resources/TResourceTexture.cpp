#include "TResourceTexture.h"

TResourceTexture::TResourceTexture(std::string name){
	m_name = name;
	LoadFile();
}

TResourceTexture::~TResourceTexture(){}

bool TResourceTexture::LoadFile(){
	return false;
}