#include "TResourceMesh.h"

TResourceMesh::TResourceMesh(std::string name){
	m_name = name;
	LoadFile();
}

TResourceMesh::~TResourceMesh(){}

bool TResourceMesh::LoadFile(){
	return false;
}