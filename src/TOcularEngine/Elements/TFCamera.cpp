#include "TFCamera.h"

TFCamera::TFCamera(vector3df position, vector3df rotation, bool perspective) : TFNode(){

}

TFCamera::~TFCamera(){

}

void TFCamera::CreateEstructure(){
	m_meshNode = new TNode();

	TTransform* pos = new TTransform();
	TTransform* rot = new TTransform();
	TCamera* camera = new TCamera();

	m_rotationNode = new TNode(rot);
	m_positionNode = new TNode(m_rotationNode, pos);
	m_meshNode = new TNode(m_positionNode, camera);
}

void TFCamera::SetPerspective(){

}

void TFCamera::SetNearFar(){

}

void TFCamera::SetLeftRight(){

}

void TFCamera::SetUpDown(){

}