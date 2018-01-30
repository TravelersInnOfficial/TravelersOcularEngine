#include "./TNode.h"

TNode::TNode(){
	m_entity = NULL;
	m_parent = NULL;
}

TNode::~TNode(){
	// -----------------------------------IMPORTANTE-------------------------------
	// Pensar donde destruir la entidad, el padre y los hijos
	// Ninguno se crea directamente detro de la clase
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
	// -----------------------------------IMPORTANTE-------------------------------
	// Que hacer en el caso de que ya hubiera una entidad asiganda al nodo
	if(m_entity!=NULL){
		// delete m_entity ??
	}
	m_entity = entity;
	return true;
}

TEntity* TNode::GetEntity(){
	return m_entity;
}

TNode* TNode::GetParent(){
	return m_parent;
}

void TNode::Draw(){
	// -----------------------------------IMPORTANTE-------------------------------
	// Aun no se hace nada aqui
	m_entity->BeginDraw();	//m_entity != NULL?
	int size = m_children.size();
	for(int i=0; i<size; i++){
		TNode* child = m_children[i];	// Pintamos cada uno de los hijos del nodo
		child->Draw();
	}
	m_entity->EndDraw();	//m_entity != NULL?
}