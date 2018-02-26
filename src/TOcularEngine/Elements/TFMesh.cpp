#include "TFMesh.h"

TFMesh::TFMesh(toe::core::TOEvector3df position, toe::core::TOEvector3df rotation, toe::core::TOEvector3df scale, std::string meshPath) : TFNode(){
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
	// Los nodos se eliminan con el arbol
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

void TFMesh::SetScale(toe::core::TOEvector3df scale){
	TTransform* myTransform = (TTransform*) m_scaleNode->GetEntity();
	myTransform->Identity();
	myTransform->Scale(scale.X, scale.Y, scale.Z);
}

void TFMesh::Scale(toe::core::TOEvector3df scale){
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

toe::core::TOEvector3df TFMesh::GetScale(){
	TTransform* myTransform = (TTransform*) m_scaleNode->GetEntity();
	glm::mat4 transformation = myTransform->GetTransform();
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(transformation, scale, rotation, translation, skew, perspective);

	toe::core::TOEvector3df toRet = toe::core::TOEvector3df(scale.x, scale.y, scale.z);
	return toRet;
}