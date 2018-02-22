#include "TFMesh.h"

TFMesh::TFMesh(vector3df position, vector3df rotation, vector3df scale, std::string meshPath) : TFNode(){
	//crere
	TTransform* t = (TTransform*) m_positionNode->GetEntity();
	t->Translate(position.X, position.Y, position.Z);
	
	t = (TTransform*) m_rotationNode->GetEntity();
	t->Rotate(1,0,0,scale.X);
	t->Rotate(0,1,0,scale.Y);
	t->Rotate(0,0,1,scale.Z);

	t = (TTransform*) m_scaleNode->GetEntity();
	t->Scale(rotation.X, rotation.Y, rotation.Z);

	//m_meshNode.GetEntity()->
}

TFMesh::~TFMesh(){

}

void TFMesh::CreateEstructure(){
	m_meshNode = new TNode();

	TTransform* pos = new TTransform();
	TTransform* rot = new TTransform();
	TTransform* esc = new TTransform();
	TMesh* mesh = new TMesh();

	m_rotationNode = new TNode(rot);
	m_scaleNode = new TNode(m_rotationNode, esc);
	m_positionNode = new TNode(m_scaleNode, pos);
	m_meshNode = new TNode(m_positionNode, mesh);
}

void TFMesh::SetScale(vector3df scale){
	
}

void TFMesh::Scale(vector3df scale){
	
}

void TFMesh::SetTexture(std::string texturePath){
	
}

void TFMesh::SetMesh(std::string meshPath){
	
}

void TFMesh::CreateCube(){
	
}