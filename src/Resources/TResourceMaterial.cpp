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
	bool toRet = false;
	
	SetLoaded(toRet);
	return toRet;
}