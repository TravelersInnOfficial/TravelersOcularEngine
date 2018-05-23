#ifndef TNODE_H
#define TNODE_H

#include "./Entities/TEntity.h"

#include <vector>

class TNode{
public:
	/**
	 * @brief	- Constructor de la clase nodo en la que inicializamos los valores a null 
	 */
	TNode();

	/**
	 * @brief	- Constructor de la clase nodo en la que se pasa la entidad por parametros 
	 * 
	 * @param 	- entity - Entidad a utilizar en el nodo 
	 */
	TNode(TEntity* entity);

	/**
	 * @brief	- Constructor de la clase nodo en la que se pasa la entidad y el nodo padre 
	 * 
	 * @param 	- parent - Nodo padre del nodo actual 
	 * @param 	- entity - Entidad a utilizar en el nodo 
	 */
	TNode(TNode* parent, TEntity* entity);
	
	/**
	 * @brief	- Destructor de la clase nodo 
	 */
	virtual ~TNode();

	/**
	 * @brief	- Le asigna la entidad al nodo 
	 * 
	 * @param 	- entity - Entidad a asignarle
	 * @return 	- bool - En el caso de que el nodo ya tuviera una entidad no se almacena y devuelve false
	 */
	bool 		SetEntity(TEntity* entity);		

	/**
	 * @brief	- Cambia el padre del nodo 
	 * 
	 * @param 	- parent - Nodo que va a ser el nuevo padre 
	 * @return 	- bool - El cambio se ha hecho de forma correcto
	 */
	bool 		SetParent(TNode* parent);

	/**
	 * @brief	- Anyade un hijo al vector de hijos del nodo 
	 * 
	 * @param 	- child - Nodo que anyadir a los hijos 
	 * @return 	- int - posicion que ha tomado el nodo en el vector
	 */
	int 		AddChild(TNode* child);			

	/**
	 * @brief	- Anya un hijo al vector de hijos del nodo en la primera posicion 
	 * 
	 * @param 	- child - Nodo que anyadir a los hijos 
	 * @return 	- int - Posicion que ha toma el nodo en el vector
	 */
	int 		AddFirstChild(TNode* child);

	/**
	 * @brief	- Quita un nodo del vector de hijos 
	 * 
	 * @param 	- child - Nodo a quitar del vector 
	 * @return 	- int - Posicion en la que se encontraba el nodo
	 */
	int 		RemoveChild(TNode* child);

	/**
	 * @brief	- Pintamos el nodo 
	 */
	virtual 	void Draw();					

	/**
	 * @brief	- Pintamos las sombras del nodo 
	 */
	void DrawShadows();						

	/**
	 * @brief	- Devuelve la entidad almacenada en el nodo 
	 * 
	 * @return	- TEntity - Entidad almacenada en el nodo 
	 */
	TEntity*	GetEntity();					

	/**
	 * @brief	- Devuelve el nodo padre del actual 
	 *
	 * @return 	- TNode - Nodo padre del actual
	 */
	TNode*		GetParent();					

	/**
	 * @brief	- Devuelve un vector con todos los hijos del nodo 
	 *
	 * @return	- Vector de hijos del nodo 
	 */
	std::vector<TNode*>	GetChildren();			

	/**
	 * @brief	- Consigue la transformacion del arbol desde la raiz del arbol hasta el nodo actual 
	 * 
	 * @return 	- glm::mat4 - Matriz transformacion de la raiz  hasta el nodo actual
	 */
	glm::mat4	GetTransformMatrix();

	/**
	 * @brief	- Devuelve la translacion que acumula el nodo actual 

	 * @return 	- glm::vec3 - Translacion 
	 */
	glm::vec3  	GetTranslation();				

	/**
	 * @brief	- Devuelve la rotacion que acumula el nodo actual 
 	 *
	 * @return	- glm::vec3 - Rotacion 
	 */
	glm::vec3  	GetRotation();

	/**
	 * @brief	- Devuelve el escalado que acumula el nodo actual 
	 *
	 * @return	- glm::vec3 - Escalado 
	 */
	glm::vec3  	GetScale();

protected:
	TEntity*			m_entity;				// m_entity - Entidad que marca el tipo de nodo, con sus propias funciones
	std::vector<TNode*>	m_children;				// m_children - Vector de nodos hijos
	TNode*				m_parent;				// m_parent - Nodo padre al actual
	
};

#endif