#include "TResourceMesh.h"

TResourceMesh::TResourceMesh(std::string name){
	m_name = name;
	LoadFile();
}

TResourceMesh::TResourceMesh(){

}

TResourceMesh::~TResourceMesh(){

}

bool TResourceMesh::LoadFile(){
	bool toRet = false;

	SetLoaded(toRet);
	return toRet;
}