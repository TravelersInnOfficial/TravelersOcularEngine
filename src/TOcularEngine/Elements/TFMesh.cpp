#include "TFMesh.h"
#include "./../../EngineUtilities/Entities/TTransform.h"
#include "./../../EngineUtilities/Entities/TMesh.h"
#include "./../../EngineUtilities/TNode.h"
#include "./../VideoDriver.h"

TFMesh::TFMesh(toe::core::TOEvector3df position, toe::core::TOEvector3df rotation, toe::core::TOEvector3df scale, std::string meshPath) : TFNode(){	
	TTransform*  t = (TTransform*) m_scaleNode->GetEntity();
	t->Scale(scale.X, scale.Y, scale.Z);

	t = (TTransform*) m_rotationNode->GetEntity();
	t->Rotate(rotation.X, rotation.Y, rotation.Z);

	t = (TTransform*) m_positionNode->GetEntity();
	t->Translate(position.X, position.Y, position.Z);

	m_entityNode->SetEntity(new TMesh(meshPath));
}

TFMesh::~TFMesh(){
}

void TFMesh::SetTexture(std::string texturePath){
	TMesh* myMesh = (TMesh*) m_entityNode->GetEntity();
	myMesh->ChangeTexture(texturePath);
}

void TFMesh::SetMesh(std::string meshPath){
	TMesh* myMesh = (TMesh*) m_entityNode->GetEntity();
	myMesh->LoadMesh(meshPath);
}

void TFMesh::CreateCube(){
	TMesh* myMesh = (TMesh*) m_entityNode->GetEntity();
	myMesh->LoadMesh("");
}

void TFMesh::CreateSphere(){
	TMesh* myMesh = (TMesh*) m_entityNode->GetEntity();
	myMesh->LoadMesh(VideoDriver::GetInstance()->GetAssetsPath() + "/models/sphere.obj");
}