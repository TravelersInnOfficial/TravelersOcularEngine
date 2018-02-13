#include "TResourceMaterial.h"

TResourceMaterial::TResourceMaterial(std::string name){
	m_name = name;
	LoadFile();
}

TResourceMaterial::~TResourceMaterial(){}

bool TResourceMaterial::LoadFile(){
	return false;
}