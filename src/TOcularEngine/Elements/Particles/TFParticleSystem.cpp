#include "./TFParticleSystem.h"
#include "./../../../EngineUtilities/Entities/TTransform.h"
#include "./../../../EngineUtilities/Entities/TParticleSystem.h"
#include "./../../../EngineUtilities/TNode.h"
#include "./../../VideoDriver.h"

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
	glm::vec3 currentPosition = m_entityNode->GetTranslation();
	glm::vec3 diffPosition = glm::vec3(currentPosition.x - translation.X, 
									   currentPosition.y - translation.Y, 
									   currentPosition.z - translation.Z);

	TParticleSystem* mySystem = (TParticleSystem*)m_entityNode->GetEntity();
	mySystem->SetTranslate(diffPosition);
	
	TFNode::SetTranslate(translation);
}

void TFParticleSystem::SetTexture(std::string path){
	TParticleSystem* mySystem = (TParticleSystem*)m_entityNode->GetEntity();
	mySystem->SetTexture(path);
}

void TFParticleSystem::SetManager(ParticleManager* manager){
	TParticleSystem* mySystem = (TParticleSystem*)m_entityNode->GetEntity();
	mySystem->SetManager(manager);
}

void TFParticleSystem::Update(float deltaTime){
	TParticleSystem* mySystem = (TParticleSystem*)m_entityNode->GetEntity();
	mySystem->Update(deltaTime);
}

void TFParticleSystem::SetNewPerSecond(int newPerSecond){
	TParticleSystem* mySystem = (TParticleSystem*)m_entityNode->GetEntity();
	mySystem->SetNewPerSecond(newPerSecond);
}

int TFParticleSystem::GetNewPerSecond(){
	TParticleSystem* mySystem = (TParticleSystem*)m_entityNode->GetEntity();
	return mySystem->GetNewPerSecond();
}