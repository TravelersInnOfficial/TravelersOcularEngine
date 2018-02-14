#include "TResource.h"

TResource::TResource(){

}

TResource::~TResource(){

}

std::string TResource::GetName(){
	return m_name;
}

void TResource::SetName(std::string name){
	// Treat name!
	m_name = name;
}

bool TResource::GetLoaded(){
	return m_loaded;
}

void TResource::SetLoaded(bool loaded){
	m_loaded = loaded;
}