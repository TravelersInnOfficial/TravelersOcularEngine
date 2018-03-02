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
	// Nos encargamos primero de eliminar todos los hijos
	int size = m_children.size();
	for(int i=size-1; i>=0; i--){
		TFNode* node = m_children[i];
		m_children.erase(m_children.begin() + i);
		delete node;
	}

	// Seguidamente eliminamos todos los billboards
	DeleteAllBillboard();

	//  Para finalizar le quitamos el padre y lo eliminamos
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
	if(parent != m_parent){
		if(m_parent != nullptr){
			m_parent->RemoveChild(this);
		}
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

void TFNode::DeleteAllBillboard(){
	int size = m_billboards.size();
	for(int i=0; i<size; i++){
		// Eliminamos el billboard en el caso de que haya uno
		if(m_billboards[i] != nullptr){
			delete m_billboards[i];
		}
	}
	// Dejamos el vector limpio a 0
	m_billboards.clear();
}

void TFNode::DeleteBillboard(int id){
	int size = m_billboards.size();
	if(id>=0 && id<size){
		// Comprobamos que existe el billboard
		if(m_billboards[id] != nullptr){
			// Eliminamos el TFNode que habia en esa posicion
			delete m_billboards[id];
			// Liberamos la posicion que este ocupaba
			m_billboards[id] = nullptr;
		}
	}
}

void TFNode::SetBillboardSize(float charSize, int id){
	int size = m_billboards.size();
	if(id>=0 && id<size){
		// Comprobamos que exista antes
		if(m_billboards[id] != nullptr){
			m_billboards[id]->SetSize(charSize);
		}
	}
}

void TFNode::SetBillboardText(std::string text, int id){
	int size = m_billboards.size();
	if(id>=0 && id<size){
		// Comprobamos que exista antes
		if(m_billboards[id] != nullptr){
			m_billboards[id]->SetText(text);
		}
	}
}

void TFNode::DeleteChildren(){}

int TFNode::AddBillboard(toe::core::TOEvector3df position, std::string text, float charSize, std::string texture){
	// Ponemos la rotacion a 0, en si no se llegara a rotar nunca el billboard
	toe::core::TOEvector3df rotation 	= toe::core::TOEvector3df(0, 0, 0);
	// La escala por defecto la pondremos a 1
	toe::core::TOEvector3df scale 		= toe::core::TOEvector3df(1, 1, 1);

	TFText* myText = new TFText(position, rotation, scale, text, charSize, texture);
	
	myText->Attach(m_positionNode);

	// Miramos si hay un hueco vacio en el vector de billboards
	int size = m_billboards.size();
	for(int i=0; i<size; i++){
		// En el caso de que haya un hueco vacio lo ponemos en esa posicion
		if(m_billboards[i]==nullptr){
			m_billboards[i] = myText;
			return i;
		}
	}
	// En el caso de no haber encontrado ninguna posicion libre lo anyadimos al final
	m_billboards.push_back(myText);
	return size;
}