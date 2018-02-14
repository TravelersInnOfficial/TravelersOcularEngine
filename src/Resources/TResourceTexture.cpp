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
	return false;
}

bool TResourceTexture::LoadFile(std::string name){
	SetName(name);
	return false;
}