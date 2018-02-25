#include "TFMesh.h"

TFMesh::TFMesh(toe::core::vector3df position, toe::core::vector3df rotation, toe::core::vector3df scale, std::string meshPath) : TFNode(){
	CreateEstructure();
	
	TTransform* t = (TTransform*) m_positionNode->GetEntity();
	t->Translate(position.X, position.Y, position.Z);
	
	t = (TTransform*) m_rotationNode->GetEntity();
	t->Rotate(rotation.X, rotation.Y, rotation.Z);

	t = (TTransform*) m_scaleNode->GetEntity();
	t->Scale(scale.X, scale.Y, scale.Z);

	m_entityNode->SetEntity(new TMesh(meshPath));
}

TFMesh::~TFMesh(){
	delete m_rotationNode;
	delete m_positionNode;
	delete m_entityNode;
}

void TFMesh::CreateEstructure(){
	TTransform* pos = new TTransform();
	TTransform* rot = new TTransform();
	TTransform* esc = new TTransform();

	m_rotationNode = new TNode(rot);
	m_scaleNode = new TNode(m_rotationNode, esc);
	m_positionNode = new TNode(m_scaleNode, pos);
	m_entityNode = new TNode();
	m_entityNode->SetParent(m_positionNode);
}

void TFMesh::SetScale(toe::core::vector3df scale){
	TTransform* myTransform = (TTransform*) m_scaleNode->GetEntity();
	myTransform->Identity();
	myTransform->Scale(scale.X, scale.Y, scale.Z);
}

void TFMesh::Scale(toe::core::vector3df scale){
	TTransform* myTransform = (TTransform*) m_scaleNode->GetEntity();
	myTransform->Scale(scale.X, scale.Y, scale.Z);
}

void TFMesh::SetTexture(std::string texturePath){
	TMesh* myMesh = (TMesh*) m_scaleNode->GetEntity();
	myMesh->ChangeTexture(texturePath);
}

void TFMesh::SetMesh(std::string meshPath){
	TMesh* myMesh = (TMesh*) m_scaleNode->GetEntity();
	myMesh->LoadMesh(meshPath);
}

void TFMesh::CreateCube(){
	TMesh* myMesh = (TMesh*) m_scaleNode->GetEntity();
	myMesh->LoadMesh("");
}

toe::core::vector3df TFMesh::GetScale(){
	toe::core::vector3df toRet = toe::core::vector3df(0,0,0);
	return toRet;
}