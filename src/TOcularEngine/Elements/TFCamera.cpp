#include "TFCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include "./../../EngineUtilities/Entities/TTransform.h"
#include "./../../EngineUtilities/Entities/TCamera.h"
#include "./../../EngineUtilities/TNode.h"

TFCamera::TFCamera(toe::core::TOEvector3df position, toe::core::TOEvector3df rotation, bool perspective) : TFNode(){
	TTransform* t = (TTransform*) m_scaleNode->GetEntity();
	t->Scale(1.0f, 1.0f, 1.0f);

	t = (TTransform*) m_rotationNode->GetEntity();
	t->Rotate(rotation.X, rotation.Y, rotation.Z);

	t = (TTransform*) m_positionNode->GetEntity();
	t->Translate(position.X, position.Y, position.Z);

	m_entityNode->SetEntity(new TCamera(perspective));
}

TFCamera::~TFCamera(){
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

void TFCamera::LookAt(toe::core::TOEvector3df target, toe::core::TOEvector3df up){
	glm::vec3 position 	= m_positionNode->GetTranslation();
	glm::vec3 targetPos	= glm::vec3(target.X, target.Y, target.Z);
	glm::vec3 upForward = glm::vec3(1, 0, 0);

	glm::mat4 matrix = glm::lookAt(position, targetPos, upForward);
	TTransform* rotation = (TTransform*) m_rotationNode->GetEntity();
   
   	rotation->Load(matrix);

}
