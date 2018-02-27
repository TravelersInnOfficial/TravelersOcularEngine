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

void TFNode::SetTranslate(toe::core::TOEvector3df translation){
	TTransform* myTransform = (TTransform*) m_positionNode->GetEntity();
	myTransform->Identity();
	myTransform->Translate(translation.X, translation.Y, translation.Z);
}

void TFNode::SetRotation(toe::core::TOEvector3df rotation){
	TTransform* myTransform = (TTransform*) m_rotationNode->GetEntity();
	myTransform->Identity();
	myTransform->Rotate(rotation.X, rotation.Y, rotation.Z);
}


void TFNode::Translate(toe::core::TOEvector3df translation){
	TTransform* myTransform = (TTransform*) m_positionNode->GetEntity();
	myTransform->Translate(translation.X, translation.Y, translation.Z);
}

void TFNode::Rotate(toe::core::TOEvector3df rotation){
	TTransform* myTransform = (TTransform*) m_rotationNode->GetEntity();
	myTransform->Rotate(rotation.X, rotation.Y, rotation.Z);
}

toe::core::TOEvector3df TFNode::GetTranslation(){
	glm::vec3 traslation = m_positionNode->GetTraslation();
	toe::core::TOEvector3df toRet = toe::core::TOEvector3df(traslation.x,traslation.y,traslation.z);
	return toRet;
}

toe::core::TOEvector3df TFNode::GetRotation(){
	glm::vec3 rotation = m_positionNode->GetRotation();
	toe::core::TOEvector3df toRet = toe::core::TOEvector3df(rotation.x,rotation.y,rotation.z);
	return toRet;
}