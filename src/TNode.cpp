#include "./TNode.h"
#include <iostream>

TNode::TNode(TEntity* entity){
	m_parent = NULL;
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
	//std::cout<<"N hijos de "<< this << ": " << size << "\n";
	
	for(int i=0; i<size; i++){
		TNode* node = m_children[i];
		//std::cout<<"Borrando Hijo "<< i << ": " << node << "\n";
		if(node != NULL){
			m_children.erase(m_children.begin());
			delete node;
			//std::cout<<"Hijo "<< i << ": " << node << " Borrado\n";
			node = NULL;
		}
		//std::cout<<"Vamos a borrar al hijo " << i+1 << " nodo actual: " << node << "\n";
	}

	if(m_entity != NULL){
		delete m_entity;
		m_entity = NULL;
	}

	if(m_parent!=NULL)
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
	
	if(m_entity == NULL){
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
	if(parent != NULL){
	
		if(m_parent != NULL){
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
	m_entity->BeginDraw();	//m_entity != NULL?
	int size = m_children.size();
	for(int i=0; i<size; i++){
		TNode* child = m_children[i];	// Pintamos cada uno de los hijos del nodo
		child->Draw();
	}
	//std::cout<<"Desapilamos NODO: "<<this<<"\n";
	m_entity->EndDraw();	//m_entity != NULL?
}