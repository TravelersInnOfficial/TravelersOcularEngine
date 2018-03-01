#include "TFNode.h"
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

/*
* ADD CHILD:
* 		1.- Compruebo si no lo tenia ya en mi vector
* 			1.1.- Si me tenia no hago nada
* 		2.- Me meto en el vector de hijos
* 		4.- Hago un SetParent del TFNode hijo con mi TFNode
*/
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

/*
* REMOVE CHILD:
* 		1.- Compruebo si lo tengo en mi vector
* 			1.1.- Si lo tengo, le hago un SetParent a mi padre (null si no existe)
* 			1.2.- Si no lo tengo no hago nada
*/
void TFNode::RemoveChild(TFNode* children){
	bool exists = false;

	for(int i = 0; i < m_children.size() && !exists; i++){
		if (m_children.at(i) == children){
			m_children.erase(m_children.begin() + i);
			children->SetParent(m_parent);
			exists = true;
		}
	}
}

/*
* SET PARENT:
* 		1.- Compruebo si mi padre es NULL
* 			1.1.- Si mi padre no es NULL...
* 				1.1.1.- Si es el mismo, no hago nada
* 				1.1.2.- Si es otro lo pongo a NULL y le hago un RemoveChild de mi mismo
* 		2.- Ahora añado al nuevo nodo como mi padre
* 		3.- Vinculo mi TNode Posicion a su TNode Rotacion como hijo (Mi posicion tiene de hijo su rotacion con Attach)
* 		4.- Accedo a mi nuevo padre y le hago un AddChild, metiendome a mi mismo
*/
void TFNode::SetParent(TFNode* parent){
	if(parent == nullptr){
		RemoveParent();
	}
	else if(parent != m_parent){
		m_parent = parent;
		TNode* node = m_parent->m_positionNode;
		Attach(node);
		m_parent->AddChild(this);
	}
}

/*
* Remove Parent:
* 	 	1.- Compruebo si mi padre es NULL
*			1.1.- Si mi padre es NULL no hago nada
* 		1.- Desvinculo el TNode Rotacion del TNode Posicion del padre y se lo vinculo al ROOT (Con Attach)
*		2.- Pongo a mi Parent a NULL
* 		3.- Cojo a mi antiguo padre y le hago un Remove Child de mi
*/
void TFNode::RemoveParent(){
	if(m_parent != nullptr){
		TFNode* parentToRemove = m_parent;	// Nos guardamos el padre al que queremos quitarle el hijo
		m_parent = nullptr;					// Ponemos el PADRE a NULL
		parentToRemove->RemoveChild(this);	// Le quitamos el hijo al padre (Lo que hara que se le ponga al abuelo como hijo) ---> SOLO SE SUBE UN NIVEL, EL ATTACH SE HACE EN EL SET PARENT
	}
	if(m_parent == nullptr) Attach(VideoDriver::GetInstance()->GetSceneManager()->GetRootNode());	// Si no tiene padre, se lo metemos al nodo ROOT
}

TFNode* TFNode::GetParent(){
	return m_parent;
}

std::vector<TFNode*> TFNode::GetChildren(){
	return m_children;
}