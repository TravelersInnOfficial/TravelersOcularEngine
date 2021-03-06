#include "TFDome.h"
#include "./../../EngineUtilities/Entities/TTransform.h"
#include "./../../EngineUtilities/TNode.h"
#include "./../../EngineUtilities/Entities/TDome.h"

TFDome::TFDome( TOEvector3df position, 
                TOEvector3df rotation, 
                TOEvector3df scale, 
                std::string texturePath): TFNode()
{

    TTransform*  t = (TTransform*) m_scaleNode->GetEntity();
	t->Scale(scale.X, scale.Y, scale.Z);

	t = (TTransform*) m_rotationNode->GetEntity();
	t->Rotate(rotation.X, rotation.Y, rotation.Z);

	t = (TTransform*) m_positionNode->GetEntity();
	t->Translate(position.X, position.Y, position.Z);

	m_entityNode->SetEntity(new TDome(texturePath));

	m_entity = TDOME_ENTITY;
}
TFDome::~TFDome(){}

void TFDome::SetTexture(std::string texturePath){
	TMesh* myMesh = (TMesh*) m_entityNode->GetEntity();
	myMesh->ChangeTexture(texturePath);
}