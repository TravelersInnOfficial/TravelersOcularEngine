#include "./TFText.h"
#include "./../../EngineUtilities/Entities/TTransform.h"
#include "./../../EngineUtilities/Entities/TText.h"
#include "./../../EngineUtilities/TNode.h"

TFText::TFText(	TOEvector3df position, TOEvector3df rotation, TOEvector3df scale, std::string text, float charSize, std::string texture):TFNode(){
	TTransform*  t = (TTransform*) m_scaleNode->GetEntity();
	t->Scale(scale.X, scale.Y, scale.Z);

	t = (TTransform*) m_rotationNode->GetEntity();
	t->Rotate(rotation.X, rotation.Y, rotation.Z);

	t = (TTransform*) m_positionNode->GetEntity();
	t->Translate(position.X, position.Y, position.Z);

	m_entityNode->SetEntity(new TText(text, charSize, texture));

	m_entity = TTEXT_ENTITY;
}

TFText::~TFText(){}

void TFText::SetText(std::string text){
	TText* myText = (TText*)m_entityNode->GetEntity();
	myText->ChangeText(text);
}

void TFText::SetSize(float charSize){
	TText* myText = (TText*)m_entityNode->GetEntity();
	myText->ChangeSize(charSize);
}