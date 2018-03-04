#include "TFRect.h"
#include "./../../EngineUtilities/Entities/TTransform.h"
#include "./../../EngineUtilities/Entities/TRect.h"
#include "./../../EngineUtilities/TNode.h"

TFRect::TFRect(toe::core::TOEvector2df size,
		toe::core::TOEvector2df position,
		float rotation,
		std::string texture){

    TTransform* t;

    t = (TTransform*) m_rotationNode->GetEntity();
	t->Rotate(0, 0, 0);

	t = (TTransform*) m_scaleNode->GetEntity();
	t->Scale(1, 1, 1);

	t = (TTransform*) m_positionNode->GetEntity();
	t->Translate(position.X, position.Y, 0);

	m_entityNode->SetEntity(new TRect(size, texture));
}

TFRect::~TFRect(){

}