#include "TFNode.h"
#include "./TFText.h"
#include "./../SceneManager.h"
#include "./../VideoDriver.h"

TFNode::TFNode(){
	TTransform* rot = new TTransform();
	m_rotationNode = new TNode(rot);

	TTransform* esc = new TTransform();
	m_scaleNode = new TNode(m_rotationNode, esc);
	
	TTransform* pos = new TTransform();
	m_positionNode = new TNode(m_scaleNode, pos);

	m_entityNode = new TNode();
	m_entityNode->SetParent(m_positionNode);

	m_parent = nullptr;
}

TFNode::~TFNode(){
	RemoveParent();
	delete m_rotationNode;
}

void TFNode::Attach(TNode* root){
	m_rotationNode->SetParent(root);
}

void TFNode::SetTranslate(toe::core::TOEvector3df translation){
	TTransform* myTransform = (TTransform*) m_positionNode->GetEntity();
	myTransform->Identity();
	myTransform->Translate(translation.X, translation.Y, translation.Z);
}

void TFNode::SetRotation(toe::core::TOEvector3df rotation){
	TTransform* myTransform = (TTransform*) m_rotationNode->GetEntity();
	myTransform->Identity();
	myTransform->Rotate(rotation.X, rotation.Y, rotation.Z);
}

void TFNode::SetScale(toe::core::TOEvector3df scale){
	TTransform* myTransform = (TTransform*) m_scaleNode->GetEntity();
	myTransform->Identity();
	myTransform->Scale(scale.X, scale.Y, scale.Z);
}

void TFNode::Translate(toe::core::TOEvector3df translation){
	TTransform* myTransform = (TTransform*) m_positionNode->GetEntity();
	myTransform->Translate(translation.X, translation.Y, translation.Z);
}

void TFNode::Rotate(toe::core::TOEvector3df rotation){
	TTransform* myTransform = (TTransform*) m_rotationNode->GetEntity();
	myTransform->Rotate(rotation.X, rotation.Y, rotation.Z);
}

void TFNode::Scale(toe::core::TOEvector3df scale){
	TTransform* myTransform = (TTransform*) m_scaleNode->GetEntity();
	myTransform->Scale(scale.X, scale.Y, scale.Z);
}

toe::core::TOEvector3df TFNode::GetTranslation(){
	glm::vec3 traslation = m_positionNode->GetTraslation();
	toe::core::TOEvector3df toRet = toe::core::TOEvector3df(traslation.x,traslation.y,traslation.z);
	return toRet;
}

toe::core::TOEvector3df TFNode::GetRotation(){
	glm::vec3 rotation = m_positionNode->GetRotation();
	toe::core::TOEvector3df toRet = toe::core::TOEvector3df(rotation.x,rotation.y,rotation.z);
	return toRet;
}

toe::core::TOEvector3df TFNode::GetScale(){
	glm::vec3 scale = m_positionNode->GetScale();
	toe::core::TOEvector3df toRet = toe::core::TOEvector3df(scale.x,scale.y,scale.z);
	return toRet;
}

void TFNode::AddChild(TFNode* children){
	bool exists = false;
	
	for(int i = 0; i < m_children.size() && !exists ; i++){
		if (m_children.at(i) == children) exists = true;
	}

	if(!exists){
		m_children.push_back(children);
		children->SetParent(this);
	}
}

void TFNode::RemoveChild(TFNode* children){
	bool exists = false;

	for(int i = 0; i < m_children.size() && !exists; i++){
		if (m_children.at(i) == children){
			m_children.erase(m_children.begin() + i);
			children->RemoveParent();
			exists = true;
		}
	}
}

void TFNode::RemoveAllChildren(){
	std::cout<<m_children.size()<<std::endl;
	for(int i = m_children.size() - 1; i >= 0; i--) RemoveChild(m_children.at(i));
	m_children.clear();
	std::cout<<m_children.size()<<std::endl;
}

std::vector<TFNode*> TFNode::GetChildren(){
	return m_children;
}

void TFNode::SetParent(TFNode* parent){
	if(parent == nullptr && parent != m_parent){
		m_parent = parent;
		Attach(m_parent->m_positionNode);
		m_parent->AddChild(this);
	}
}

void TFNode::RemoveParent(){
	if(m_parent != nullptr){
		TFNode* parentToRemove = m_parent;	// Nos guardamos el padre al que queremos quitarle el hijo
		m_parent = nullptr;					// Ponemos el PADRE a NULL
		parentToRemove->RemoveChild(this);	// Le quitamos el hijo al padre (Lo que hara que se le ponga al abuelo como hijo) ---> SOLO SE SUBE UN NIVEL, EL ATTACH SE HACE EN EL SET PARENT
		Attach(VideoDriver::GetInstance()->GetSceneManager()->GetRootNode());	// Se lo metemos al nodo ROOT
	}
}

TFNode* TFNode::GetParent(){
	return m_parent;
}

TFText* TFNode::AddBillboard(toe::core::TOEvector3df position, std::string text, std::string texture){
	glm::vec3 rot 	= m_rotationNode->GetRotation(); //toe::core::TOEvector3df(0, 0, 0);

	toe::core::TOEvector3df rotation 	= toe::core::TOEvector3df(-rot.x, -rot.y, -rot.z);
	//toe::core::TOEvector3df rotation 	= toe::core::TOEvector3df(90, 0, 0);
	toe::core::TOEvector3df scale 		= toe::core::TOEvector3df(1, 1, 1);

	TFText* myText = new TFText(position, rotation, scale, text, texture);
	
	m_billboards.push_back(myText);
	myText->Attach(m_positionNode);

	return myText;
}