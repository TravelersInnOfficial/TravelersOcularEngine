#include "TFAnimation.h"
#include "./../../EngineUtilities/Entities/TTransform.h"
#include "./../../EngineUtilities/Entities/TAnimation.h"
#include "./../../EngineUtilities/TNode.h"
#include "./../VideoDriver.h"

TFAnimation::TFAnimation(TOEvector3df position, TOEvector3df rotation, TOEvector3df scale) : TFNode(){	
	TTransform*  t = (TTransform*) m_scaleNode->GetEntity();
	t->Scale(scale.X, scale.Y, scale.Z);

	t = (TTransform*) m_rotationNode->GetEntity();
	t->Rotate(rotation.X, rotation.Y, rotation.Z);

	t = (TTransform*) m_positionNode->GetEntity();
	t->Translate(position.X, position.Y, position.Z);

    m_entityNode->SetEntity(new TAnimation());
	m_entity = TANIMATION_ENTITY;
}

TFAnimation::~TFAnimation(){ }

void TFAnimation::SetTexture(std::string texturePath){
	TAnimation* myAnim = (TAnimation*) m_entityNode->GetEntity();
	myAnim->ChangeTexture(texturePath);
}

void TFAnimation::SetInvisible(){
    TAnimation* myAnim = (TAnimation*) m_entityNode->GetEntity();
	myAnim->ChangeTexture(VideoDriver::GetInstance()->GetAssetsPath() + "/textures/invisible_texture.png");
}

void TFAnimation::SetBoundBox(bool visible){
	TAnimation* myAnim = (TAnimation*) m_entityNode->GetEntity();
	myAnim->SetBBVisibility(visible);
}

void TFAnimation::SetAnimationPaths(std::string ID, const std::vector<std::string> &paths, int fps){
    TAnimation* myAnim = (TAnimation*) m_entityNode->GetEntity();
	myAnim->SetPaths(ID, paths.size(), paths, fps);
}

void TFAnimation::Update(float deltatime){
	TAnimation* myAnim = (TAnimation*) m_entityNode->GetEntity();
	myAnim->UpdateAnimation(deltatime);
}

void TFAnimation::ChangeAnimation(std::string ID, int fps){
	TAnimation* myAnim = (TAnimation*) m_entityNode->GetEntity();
	myAnim->ChangeAnim(ID, fps);
}

void TFAnimation::PlayAnimation(std::string ID, int fps){
	TAnimation* myAnim = (TAnimation*) m_entityNode->GetEntity();
	myAnim->PlayAnim(ID, fps);
}

void TFAnimation::PlayAnimationAbove(std::string ID, int fps){
	TAnimation* myAnim = (TAnimation*) m_entityNode->GetEntity();
	myAnim->PlayAnimAbove(ID, fps);
}

void TFAnimation::BindSyncAnimation(TFAnimation* master){
	TAnimation* myAnim = (TAnimation*) m_entityNode->GetEntity();
	TAnimation* animMaster = (TAnimation*) master->m_entityNode->GetEntity();
	myAnim->BindSyncAnimMaster(animMaster);
}

int TFAnimation::GetAnimationFrame(){
	TAnimation* myAnim = (TAnimation*) m_entityNode->GetEntity();
	return myAnim->GetActualFrame();
}

std::string TFAnimation::GetAnimationName(){
	TAnimation* myAnim = (TAnimation*) m_entityNode->GetEntity();
	return myAnim->GetActualAnimation();
}