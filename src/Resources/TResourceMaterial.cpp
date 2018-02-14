#include "TResourceMaterial.h"

TResourceMaterial::TResourceMaterial(std::string name){
	m_name = name;
	LoadFile();
}

TResourceMaterial::TResourceMaterial(){

}

TResourceMaterial::~TResourceMaterial(){

}

bool TResourceMaterial::LoadFile(){
	toRet = false;
	
	SetLoaded(toRet);
	return toRet;
}

bool TResourceMaterial::LoadFile(std::string name){
	toRet = false;
	SetName(name);
	
	SetLoaded(toRet);
	return toRet;
}