#ifndef TNODE_H
#define TNODE_H

#include "./Entities/TEntity.h"

#include <vector>

class TNode{
public:
	TNode();
	TNode(TEntity* entity);
	TNode(TNode* parent, TEntity* entity);
	~TNode();

	int 		AddChild(TNode* child);			// Anyade un hijo al vector de hijos del nodo
	int 		RemoveChild(TNode* child);		// Quita un hijo del vector de hijos del nodo
	bool 		SetEntity(TEntity* entity);		// Le asigna la entidad al nodo
	TEntity*	GetEntity();					// Devuelve la entidad al nodo
	bool 		SetParent(TNode* parent);		// Le asigna la entidad al nodo
	TNode*		GetParent();					// Devuelve el padre del nodo
	void		Draw();							// Pinta el nodo

	std::vector<TNode*>	GetChildren();			// Devuelve todos los hijos del nodo

	glm::mat4	GetTransformMatrix();			// Consigue la matriz del arbol
	glm::vec3  	GetTranslation();				// Returns vec3 Traslation
	glm::vec3  	GetRotation();					// Returns vec3 Rotation
	glm::vec3  	GetScale();						// Returns vec3 Scale

private:
	TEntity*			m_entity;				// Entidad que marca el tipo de nodo, con sus propias funciones
	std::vector<TNode*>	m_children;				// Vector de nodos hijos
	TNode*				m_parent;				// Nodo padre al actual
	
};

#endif