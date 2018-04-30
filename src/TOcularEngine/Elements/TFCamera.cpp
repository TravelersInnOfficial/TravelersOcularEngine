#include "TFCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include "./../../EngineUtilities/Entities/TTransform.h"
#include "./../../EngineUtilities/Entities/TCamera.h"
#include "./../../EngineUtilities/TNode.h"

TFCamera::TFCamera(TOEvector3df position, TOEvector3df rotation, bool perspective) : TFNode(){
	TTransform* t = (TTransform*) m_scaleNode->GetEntity();
	t->Scale(1.0f, 1.0f, 1.0f);

	t = (TTransform*) m_rotationNode->GetEntity();
	t->Rotate(rotation.X, rotation.Y, rotation.Z);

	t = (TTransform*) m_positionNode->GetEntity();
	t->Translate(position.X, position.Y, position.Z);

	m_entityNode->SetEntity(new TCamera(perspective));

	m_entity = TCAMERA_ENTITY;
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

void TFCamera::LookAt(TOEvector3df target, TOEvector3df up){

	glm::vec3 position 	= m_entityNode->GetTranslation();
	glm::vec3 targetPos	= glm::vec3(target.X, target.Y, target.Z);

	glm::vec3 zaxis = glm::normalize(targetPos - position);
	glm::vec3 xaxis = glm::normalize(glm::cross(glm::vec3(0,1,0), zaxis));
	glm::vec3 yaxis = glm::cross(zaxis, xaxis);

	glm::mat4 matrix;
	matrix[0][0] = xaxis.x; // First column, first row
    matrix[0][1] = xaxis.y;
    matrix[0][2] = xaxis.z;
    matrix[1][0] = yaxis.x; // First column, second row
    matrix[1][1] = yaxis.y;
    matrix[1][2] = yaxis.z;
    matrix[2][0] = zaxis.x; // First column, third row
    matrix[2][1] = zaxis.y;
    matrix[2][2] = zaxis.z; 

    bool niceMatrix = true;
	if(glm::any(glm::isnan(matrix[0]))) niceMatrix = false;
	if(glm::any(glm::isnan(matrix[1]))) niceMatrix = false;
	if(glm::any(glm::isnan(matrix[2]))) niceMatrix = false;

   if(niceMatrix){
		TTransform* rotation = (TTransform*) m_rotationNode->GetEntity();
	   	rotation->Load(matrix);
	}

}
