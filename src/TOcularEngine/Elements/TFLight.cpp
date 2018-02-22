#include "TFLight.h"

TFLight::TFLight(vector3df position, vector3df rotation, vector4df color, float intensity) : TFNode(){
	
}

TFLight::~TFLight(){
	
}

void TFLight::CreateEstructure(){
	m_meshNode = new TNode();

	TTransform* pos = new TTransform();
	TTransform* rot = new TTransform();
	TLight* light = new TLight();

	m_rotationNode = new TNode(rot);
	m_positionNode = new TNode(m_rotationNode, pos);
	m_meshNode = new TNode(m_positionNode, light);
}

void TFLight::SetColor(vector4df color){
	
}

void TFLight::SetIntensity(float intensity){
	
}	