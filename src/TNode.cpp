#include "TNode.h"
#include "./Entities/TTransform.h"
#include <iostream>

TNode::TNode(){
	m_parent = nullptr;
	m_entity = nullptr;
}

TNode::TNode(TEntity* entity){
	m_parent = nullptr;
	m_entity = entity;
}

TNode::TNode(TNode* parent, TEntity* entity){
	m_parent = parent;
	m_entity = entity;
	parent->AddChild(this);
}

// -----------------------------------IMPORTANTE-------------------------------
// Pensar donde destruir la entidad, el padre y los hijos
// Ninguno se crea directamente detro de la clase
TNode::~TNode(){
	int size = m_children.size();
	//std::cout<<"Empezamos a borrar "<< this << " | Numero de hijos: " << size << "\n";
	
	for(int i=0; i<size; i++){
		TNode* node = m_children[i];
		//std::cout<<"Borrando Hijo "<< i << ": " << node << "\n";
		if(node != nullptr){
			delete node;
			//std::cout<<"Hijo "<< i << ": " << node << " Borrado\n";
			node = nullptr;
		}
	}
	m_children.clear();
	//std::cout<<"Todos los hijos borrados de: " << this << "\n";
	
	if(m_entity != nullptr){
		//std::cout<<"Borrando entidad de: " << this << "\n";	
		delete m_entity;
		m_entity = nullptr;
	}

	if(m_parent!=nullptr)
		m_parent->RemoveChild(this);
	//std::cout<<"Borrado: " << this << "\n\n";
}

int TNode::AddChild(TNode* child){
	int position = m_children.size();
	m_children.push_back(child);
	return position;	// Devolvemos la posicion en la que se pone el hijo
}

int TNode::RemoveChild(TNode* child){
	int size = m_children.size();
	for(int i=0; i<size; i++){
		TNode* node = m_children[i];
		if(node == child){
			m_children.erase(m_children.begin()+i);
			return i;	// Devolvemos la posicion en la que se encontraba el nodo
		}
	}
	return -1;	// En el caso de no encontrarlo devolvemos un -1
}


bool TNode::SetEntity(TEntity* entity){
	bool toReturn = false;
	
	if(m_entity == nullptr){
		m_entity = entity;
		toReturn = true;
	}
	
	return toReturn;
}

TEntity* TNode::GetEntity(){
	return m_entity;
}

bool TNode::SetParent(TNode* parent){
	bool toReturn = false;
	if(parent != nullptr){
	
		if(m_parent != nullptr){
			m_parent->RemoveChild(this);
		}
		m_parent = parent;
		m_parent->AddChild(this);
		
		toReturn = true;
	}
	return toReturn;
}

TNode* TNode::GetParent(){
	return m_parent;
}

void TNode::Draw(){
	//std::cout<<"Apilamos NODO: "<<this<<"\n";
	if(m_entity != nullptr) m_entity->BeginDraw();
	
	int size = m_children.size();
	for(int i=0; i<size; i++){
		TNode* child = m_children[i];	// Pintamos cada uno de los hijos del nodo
		child->Draw();
	}
	
	if(m_entity != nullptr) m_entity->EndDraw();
	//std::cout<<"Desapilamos NODO: "<<this<<"\n";
}

glm::mat4 TNode::GetTransformMatrix(){
	TNode* auxParent;
	glm::mat4 toReturn;

	auxParent = GetParent();
	toReturn = ((TTransform*)auxParent->GetEntity())->GetTransform();
	auxParent = auxParent->GetParent();

	while(auxParent != nullptr){
		toReturn = ((TTransform*)auxParent->GetEntity())->GetTransform() * toReturn;
		auxParent = auxParent->GetParent();
	}
	
	return toReturn;
}