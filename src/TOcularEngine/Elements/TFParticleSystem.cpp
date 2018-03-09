#include "./TFParticleSystem.h"
#include "./../../EngineUtilities/Entities/TTransform.h"
#include "./../../EngineUtilities/Entities/TParticleSystem.h"
#include "./../../EngineUtilities/TNode.h"
#include "./../VideoDriver.h"

TFParticleSystem::TFParticleSystem(toe::core::TOEvector3df position, toe::core::TOEvector3df rotation, toe::core::TOEvector3df scale) : TFNode(){	
	TTransform*  t = (TTransform*) m_scaleNode->GetEntity();
	t->Scale(scale.X, scale.Y, scale.Z);

	t = (TTransform*) m_rotationNode->GetEntity();
	t->Rotate(rotation.X, rotation.Y, rotation.Z);

	t = (TTransform*) m_positionNode->GetEntity();
	t->Translate(position.X, position.Y, position.Z);

	m_entityNode->SetEntity(new TParticleSystem());
}

TFParticleSystem::~TFParticleSystem(){
	
}

void TFParticleSystem::Translate(toe::core::TOEvector3df translation){
	TFNode::Translate(translation);

	TParticleSystem* mySystem = (TParticleSystem*)m_entityNode->GetEntity();
	mySystem->Translate(glm::vec3(translation.X, translation.Y, translation.Z));
}

void TFParticleSystem::SetTranslate(toe::core::TOEvector3df translation){
	TFNode::SetTranslate(translation);

	TParticleSystem* mySystem = (TParticleSystem*)m_entityNode->GetEntity();
	mySystem->SetTranslate(glm::vec3(translation.X, translation.Y, translation.Z));
}

void TFParticleSystem::SetTexture(std::string path){
	TParticleSystem* mySystem = (TParticleSystem*)m_entityNode->GetEntity();
	mySystem->SetTexture(path);
}

void TFParticleSystem::Update(float deltaTime){
	TParticleSystem* mySystem = (TParticleSystem*)m_entityNode->GetEntity();
	mySystem->Update(deltaTime);
}