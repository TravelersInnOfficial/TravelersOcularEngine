#include "TFCamera.h"

TFCamera::TFCamera(toe::core::TOEvector3df position, toe::core::TOEvector3df rotation, bool perspective) : TFNode(){
	CreateEstructure();
	
	TTransform* t = (TTransform*) m_positionNode->GetEntity();
	t->Translate(position.X, position.Y, position.Z);
	
	t = (TTransform*) m_rotationNode->GetEntity();
	t->Rotate(rotation.X, rotation.Y, rotation.Z);

	TCamera* camera = new TCamera(perspective);
	m_entityNode->SetEntity(camera);
}

TFCamera::~TFCamera(){

}

void TFCamera::CreateEstructure(){
	TTransform* pos = new TTransform();
	TTransform* rot = new TTransform();

	m_rotationNode = new TNode(rot);
	m_positionNode = new TNode(m_rotationNode, pos);
	
	m_entityNode = new TNode();
	m_entityNode->SetParent(m_positionNode);
}

void TFCamera::SetPerspective(bool perspectiveCamera){
	TCamera* myEntity = (TCamera*) m_entityNode->GetEntity();
	if(perspectiveCamera) myEntity->SetPerspective();
	else myEntity->SetParallel();
}

void TFCamera::SetNearFar(float near, float far){
	TCamera* myEntity = (TCamera*) m_entityNode->GetEntity();
	myEntity->SetNear(near);
	myEntity->SetFar(far);
}

void TFCamera::SetLeftRight(float left, float right){
	TCamera* myEntity = (TCamera*) m_entityNode->GetEntity();
	myEntity->SetLeft(left);
	myEntity->SetRight(right);
}

void TFCamera::SetTopBottom(float top, float bottom){
	TCamera* myEntity = (TCamera*) m_entityNode->GetEntity();
	myEntity->SetTop(top);
	myEntity->SetBottom(bottom);
}

bool TFCamera::GetPerspective(){
	TCamera* myEntity = (TCamera*) m_entityNode->GetEntity();
	return myEntity->GetPerspective();
}

float TFCamera::GetNear(){
	TCamera* myEntity = (TCamera*) m_entityNode->GetEntity();
	return myEntity->GetNear();
}

float TFCamera::GetFar(){
	TCamera* myEntity = (TCamera*) m_entityNode->GetEntity();
	return myEntity->GetFar();
}

float TFCamera::GetLeft(){
	TCamera* myEntity = (TCamera*) m_entityNode->GetEntity();
	return myEntity->GetLeft();
}

float TFCamera::GetRight(){
	TCamera* myEntity = (TCamera*) m_entityNode->GetEntity();
	return myEntity->GetRight();
}

float TFCamera::GetTop(){
	TCamera* myEntity = (TCamera*) m_entityNode->GetEntity();
	return myEntity->GetTop();
}

float TFCamera::GetBottom(){
	TCamera* myEntity = (TCamera*) m_entityNode->GetEntity();
	return myEntity->GetBottom();
}