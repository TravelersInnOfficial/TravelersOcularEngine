#include "TFNode.h"

TFNode::TFNode(){
	m_entityNode = nullptr;
	m_rotationNode = nullptr;
	m_positionNode = nullptr;
	CreateEstructure();
}

TFNode::~TFNode(){

}

void TFNode::SetTranslate(vector3df translation){
	TTransform* myTransform = (TTransform*) m_positionNode->GetEntity();
	myTransform->Identity();
	myTransform->Translate(translation.X, translation.Y, translation.Z);
}

void TFNode::SetRotation(vector3df rotation){
	TTransform* myTransform = (TTransform*) m_rotationNode->GetEntity();
	myTransform->Identity();
	myTransform->Rotate(rotation.X, rotation.Y, rotation.Z);
}


void TFNode::Translate(vector3df translation){
	TTransform* myTransform = (TTransform*) m_positionNode->GetEntity();
	myTransform->Translate(translation.X, translation.Y, translation.Z);
}

void TFNode::Rotate(vector3df rotation){
	TTransform* myTransform = (TTransform*) m_rotationNode->GetEntity();
	myTransform->Rotate(rotation.X, rotation.Y, rotation.Z);
}

vector3df TFNode::GetTranslate(){
	vector3df toRet = vector3df(0,0,0);
	return toRet;
}

vector3df TFNode::GetRotation(){
	vector3df toRet = vector3df(0,0,0);
	return toRet;
}