#include "TFNode.h"

TFNode::TFNode(){
	m_entityNode = nullptr;
	m_rotationNode = nullptr;
	m_positionNode = nullptr;
}

TFNode::~TFNode(){

}

void TFNode::Attach(TNode* root){
	m_rotationNode->SetParent(root);
}

void TFNode::SetTranslate(toe::core::vector3df translation){
	TTransform* myTransform = (TTransform*) m_positionNode->GetEntity();
	myTransform->Identity();
	myTransform->Translate(translation.X, translation.Y, translation.Z);
}

void TFNode::SetRotation(toe::core::vector3df rotation){
	TTransform* myTransform = (TTransform*) m_rotationNode->GetEntity();
	myTransform->Identity();
	myTransform->Rotate(rotation.X, rotation.Y, rotation.Z);
}


void TFNode::Translate(toe::core::vector3df translation){
	TTransform* myTransform = (TTransform*) m_positionNode->GetEntity();
	myTransform->Translate(translation.X, translation.Y, translation.Z);
}

void TFNode::Rotate(toe::core::vector3df rotation){
	TTransform* myTransform = (TTransform*) m_rotationNode->GetEntity();
	myTransform->Rotate(rotation.X, rotation.Y, rotation.Z);
}

toe::core::vector3df TFNode::GetTranslate(){
	toe::core::vector3df toRet = toe::core::vector3df(0,0,0);
	return toRet;
}

toe::core::vector3df TFNode::GetRotation(){
	toe::core::vector3df toRet = toe::core::vector3df(0,0,0);
	return toRet;
}