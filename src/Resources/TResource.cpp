#include "TResource.h"

TResource::TResource(){}

TResource::~TResource(){}

std::string TResource::GetName(){
	return m_name;
}

void TResource::SetName(std::string name){
	m_name = name;
}