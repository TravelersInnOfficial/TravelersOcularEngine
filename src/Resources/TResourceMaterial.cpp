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
	return false;
}

bool TResourceMaterial::LoadFile(std::string name){
	SetName(name);
	return false;
}