#include "TFLight.h"

TFLight::TFLight(toe::core::vector3df position, toe::core::vector3df rotation, toe::core::vector4df color, float intensity) : TFNode(){
	CreateEstructure();
	
	TTransform* t = (TTransform*) m_positionNode->GetEntity();
	t->Translate(position.X, position.Y, position.Z);

	t = (TTransform*) m_rotationNode->GetEntity();
	t->Rotate(rotation.X, rotation.Y, rotation.Z);

	glm::vec4 glmColor = glm::vec4(color.X, color.Y, color.X2, color.Y2);
	TColor myColor = TColor(glmColor);
	TLight* light = new TLight(myColor, intensity);
	m_entityNode->SetEntity(light);
}

TFLight::~TFLight(){

}

void TFLight::CreateEstructure(){
	TTransform* pos = new TTransform();
	TTransform* rot = new TTransform();

	m_rotationNode = new TNode(rot);
	m_positionNode = new TNode(m_rotationNode, pos);
	m_entityNode = new TNode();
	m_entityNode->SetParent(m_positionNode);
}

void TFLight::SetColor(toe::core::vector4df color){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();
	glm::vec4 glmColor = glm::vec4(color.X, color.Y, color.X2, color.Y2);
	TColor myColor = TColor(glmColor);
	myEntity->SetColor(myColor);
}

void TFLight::SetIntensity(float intensity){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();
	myEntity->SetIntensity(intensity);
}

toe::core::vector4df TFLight::GetColor(){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();
	glm::vec4 myColor = myEntity->GetColor().GetRGBA();
	toe::core::vector4df toRetColor = toe::core::vector4df(myColor.x, myColor.y, myColor.z, myColor.w);
	return toRetColor;
}

float TFLight::GetIntensity(){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();
	return myEntity->GetIntensity();
}

void TFLight::SetActive(bool active){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();
	myEntity->SetActive(active);
}

bool TFLight::GetActive(){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();
	return myEntity->GetActive();
}