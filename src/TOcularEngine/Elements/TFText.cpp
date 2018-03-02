#include "./TFText.h"

TFText::TFText(	toe::core::TOEvector3df position, toe::core::TOEvector3df rotation, toe::core::TOEvector3df scale, std::string text, std::string texture):TFNode(){
	TTransform* t = (TTransform*) m_rotationNode->GetEntity();
	t->Rotate(rotation.X, rotation.Y, rotation.Z);

	t = (TTransform*) m_scaleNode->GetEntity();
	t->Scale(scale.X, scale.Y, scale.Z);

	t = (TTransform*) m_positionNode->GetEntity();
	t->Translate(position.X, position.Y, position.Z);

	m_entityNode->SetEntity(new TText(text, texture));
}

TFText::~TFText(){}

void TFText::SetText(std::string text){
	TText* myText = (TText*)m_entityNode->GetEntity();
	myText->ChangeText(text);
}