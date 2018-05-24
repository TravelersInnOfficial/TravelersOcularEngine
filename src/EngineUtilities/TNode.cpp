#include "TNode.h"
#include "Entities/TTransform.h"
#include <glm/gtx/matrix_decompose.hpp>
#include <iostream>
#include "glm/ext.hpp"
#include <cmath>

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
	// La adjuntamos al nodo padre el nodo actual
	parent->AddChild(this);
}

TNode::~TNode(){
	// A la hora de eliminar un nodo eliminamos tambien todos los nodos hijo
	int size = m_children.size();
	for(int i = size - 1; i>=0; i--){
		TNode* node = m_children[i];
		if(node != nullptr){
			m_children.erase(m_children.begin() + i);
			delete node;
			node = nullptr;
		}
	}
	m_children.clear();
	
	// Eliminamos la entidad del nodo
	if(m_entity != nullptr){
		delete m_entity;
		m_entity = nullptr;
	}
	 
	// Quitamos el nodo actual de la lista de hijos del padre
	if(m_parent!=nullptr) m_parent->RemoveChild(this);
}

int TNode::AddChild(TNode* child){
	int position = m_children.size();
	m_children.push_back(child);
	return position;	// Devolvemos la posicion en la que se pone el hijo
}

int TNode::AddFirstChild(TNode* child){
	int position = 0;
	m_children.insert(m_children.begin(), child);
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
	
	// En el caso de que ya hubiera una entidad no la cambiamos
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
	
		// En el caso que ya tuviera un padre, le quitamos el nodo actual como hijo
		if(m_parent != nullptr){
			m_parent->RemoveChild(this);
		}
		m_parent = parent;
		
		toReturn = true;
	}
	return toReturn;
}

TNode* TNode::GetParent(){
	return m_parent;
}

void TNode::Draw(){
	if(m_entity != nullptr) m_entity->BeginDraw();
	
	int size = m_children.size();
	for(int i=0; i<size; i++){
		TNode* child = m_children[i];	// Pintamos cada uno de los hijos del nodo
		child->Draw();
	}
	
	if(m_entity != nullptr) m_entity->EndDraw();
}

void TNode::DrawShadows(){
	if(m_entity != nullptr){
		m_entity->DrawShadow();						// For mesh sets drawingShadows to true
		m_entity->BeginDraw();						// for mesh: if drawingShadowsn, doenst draw
		// ^^^^^^^^^^^^^^^^^^^^	THIS NEED TO BE DONE DUE TO STACK PUSHS AND POPS
	}
	
	int size = m_children.size();
	for(int i=0; i<size; i++){
		TNode* child = m_children[i];	// Pintamos cada uno de los hijos del nodo
		child->DrawShadows();
	}
	if(m_entity != nullptr) m_entity->EndDraw();	// For mesh sets drawingShadows to false
}

glm::mat4 TNode::GetTransformMatrix(){
	TNode* auxParent;
	glm::mat4 toReturn;

	auxParent = GetParent();
	if(auxParent != nullptr){
		// Inicializamos la variable toReturn con la transformacion del nodo padre
		toReturn = ((TTransform*)auxParent->GetEntity())->GetTransform();
		auxParent = auxParent->GetParent();
	}

	while(auxParent != nullptr){
		// Vamos acumulando transformaciones mientras vamos subiendo por el arbol
		toReturn = toReturn * ((TTransform*)auxParent->GetEntity())->GetTransform();
		auxParent = auxParent->GetParent();
	}
	
	// Al acabar tendremos la transformacion del nodo actual desde la raiz del arbol
	return toReturn;
}

glm::vec3 TNode::GetTranslation(){
	glm::mat4 myTransform = GetTransformMatrix();
	
	// Descomponemos la transformacion del nodo y devolvemos la translacion
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(myTransform, scale, rotation, translation, skew, perspective);

	return translation;
}

glm::vec3 TNode::GetRotation(){
	glm::mat4 myTransform = GetTransformMatrix();

	// Descomponemos la transformacion del nodo y nos quedamos con la rotacion
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;

	glm::decompose(myTransform, scale, rotation, translation, skew, perspective);

	// Cambiamos los valores del quad para que el angulo de elevacion se corresponda con la rotacion en X
	rotation = glm::conjugate(rotation);
	rotation = glm::quat(rotation.z, rotation.x, rotation.y, rotation.w);
	// Ya con el nuevo QUAT calculamos la rotacion de este en angulos de euler
	glm::vec3 toRet = glm::eulerAngles(rotation);

	toRet = glm::vec3(toRet.y, -toRet.x, toRet.z);
	toRet = glm::degrees(toRet);

	toRet.x = -toRet.x;
	toRet.y = -toRet.y;
	toRet.z = 180+toRet.z;

	// Despues de las operaciones tenemos en toRet la rotacion del nodo en grados

	return toRet;
}

glm::vec3 TNode::GetScale(){
	glm::mat4 myTransform = GetTransformMatrix();
	
	// Descomponemos la transforamcion del nodo y nos quedamos con el escalado
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(myTransform, scale, rotation, translation, skew, perspective);

	glm::vec3 toRet = glm::vec3(scale.x, scale.y, scale.z);
	return toRet;
}

std::vector<TNode*>	TNode::GetChildren(){
	return m_children;
}