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

toe::core::TOEvector3df TFNode::GetTranslate(){
	TTransform* myTransform = (TTransform*) m_positionNode->GetEntity();
	glm::mat4 transformation = myTransform->GetTransform();
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(transformation, scale, rotation, translation, skew, perspective);

	toe::core::TOEvector3df toRet = toe::core::TOEvector3df(translation.x, translation.y, translation.z);
	return toRet;
}

toe::core::TOEvector3df TFNode::GetRotation(){
	TTransform* myTransform = (TTransform*) m_rotationNode->GetEntity();
	glm::mat4 transformation = myTransform->GetTransform();
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(transformation, scale, rotation, translation, skew, perspective);
	
	rotation = glm::conjugate(rotation);
	glm::vec3 finalRotation = glm::eulerAngles(rotation);

	toe::core::TOEvector3df toRet = toe::core::TOEvector3df(finalRotation.x, finalRotation.y, finalRotation.z);
	return toRet;
}