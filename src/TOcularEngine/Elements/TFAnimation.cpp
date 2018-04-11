#include "TFAnimation.h"
#include "./../../EngineUtilities/Entities/TTransform.h"
#include "./../../EngineUtilities/Entities/TAnimation.h"
#include "./../../EngineUtilities/TNode.h"
#include "./../VideoDriver.h"

TFAnimation::TFAnimation(toe::core::TOEvector3df position, toe::core::TOEvector3df rotation, toe::core::TOEvector3df scale) : TFNode(){	
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

void TFAnimation::Update(float deltatime){
	TAnimation* myAnim = (TAnimation*) m_entityNode->GetEntity();
	myAnim->UpdateAnimation(deltatime);
}

void TFAnimation::SetAnimationPaths(int frames, std::string paths[]){
    TAnimation* myAnim = (TAnimation*) m_entityNode->GetEntity();
	myAnim->SetPaths(frames, paths);
}

void TFAnimation::SetTexture(std::string texturePath){
	TAnimation* myMesh = (TAnimation*) m_entityNode->GetEntity();
	myMesh->ChangeTexture(texturePath);
}

void TFAnimation::SetInvisible(){
    TAnimation* myMesh = (TAnimation*) m_entityNode->GetEntity();
	myMesh->ChangeTexture(VideoDriver::GetInstance()->GetAssetsPath() + "/textures/invisible_texture.png");
}

void TFAnimation::SetBoundBox(bool visible){
	TAnimation* myMesh = (TAnimation*) m_entityNode->GetEntity();
	myMesh->SetBBVisibility(visible);
}
