#ifndef TFNODE_H
#define TFNODE_H

/**
 * @brief Tree Node Facade.
 * 
 * @file TFNode.h
 */

#include <TOEvector3d.h>
#include <TColor.h>
#include <EntityTypes.h>
#include <vector>
#include <ShaderTypes.h>

// Forward declaration
class TFText;
class TNode;
class SceneManager;

class TFNode{
	friend class SceneManager;

public:
	/**
	 * @brief	- Cambia la posicion del nodo 
	 * 
	 * @param 	- translation - Nueva posicion
	 */
	virtual void SetTranslate(TOEvector3df translation);	

	/**
	 * @brief	- Cambia la rotacion del nodo
	 * 
	 * @param 	- rotation - NUeva rotacion
	 */
	virtual void SetRotation(TOEvector3df rotation);

	/**
	 * @brief	- Cambia el escalado del nodo 
	 * 
	 * @param 	- scale - Nuevo escalado 
	 */
	virtual void SetScale(TOEvector3df scale);		

	/**
	 * @brief	- Translada el nodo 
	 * 
	 * @param 	- translation - Valor a transladar
	 */
	virtual void Translate(TOEvector3df translation);

	/**
	 * @brief	- Rota el nodo 
	 * 
	 * @param 	- rotation - Valor a rotar 
	 */
	virtual void Rotate(TOEvector3df rotation);	

	/**
	 * @brief	- Escala el nodo 
	 * 
	 * @param 	- scale - Valor a escalar 
	 */
	virtual void Scale(TOEvector3df scale);				

	/**
	 * @brief	- Devuelve la translacion del nodo 
	 *
	 * @return	- Translacion del nodo 
	 */
	virtual TOEvector3df GetTranslation();

	/**
	 * @brief	- Devuelve la rotacion del nodo 
	 *
	 * @return 	- Rotacion del nodo
	 */
	virtual TOEvector3df GetRotation();

	/**
	 * @brief	- Devuelve el escalado del nodo 
	 *
	 * @return	- Escalado del nodo 
	 */
	virtual TOEvector3df GetScale();		

	/**
	 * @brief	- Anyade un nodo como hijo del actual 
	 * 
	 * @param 	- children - Nodo que poner como hijo 
	 * @return 	- bool - Si se ha anyadido correctamente
	 */
	virtual bool AddChild(TFNode* children);

	/**
	 * @brief	- Elimina un hijo del nodo 
	 * 
	 * @param 	- children - Nodo a eliminar como hijo 
	 * @return 	- bool - Si el nodo se ha eliminado correctamente
	 */
	bool RemoveChild(TFNode* children);		

	/**
	 * @brief	- Elimina todos los hijos del nodo 
	 */
	void RemoveAllChildren();				

	/**
	 * @brief	- Cambia el padre del nodo 
	 * 
	 * @param 	- parent - Nuevo paddro 
	 */
	void SetParent(TFNode* parent = nullptr);	

	/**
	 * @brief	- Elimina el padre del nodo 
	 */
	void RemoveParent();

	/**
	 * @brief	- Devuelve el padre del nodo 
	 */
	TFNode* GetParent();

	/**
	 * @brief	- Devuelve un vector con todos los hijos del nodo 
	 */
	std::vector<TFNode*> GetChildren();

	/**
	 * @brief	- Anyade un billboard al nodo 
	 * 
	 * @param 	- position - Posicion del billboard
	 * @param 	- text - Cadena de texto del billboard 
	 * @param 	- charSize - Tamanyo de los caracteres
	 * @param 	- texture - Ruta a la textura con el mapa de caracteres
	 * @return 	- int - Devuelve la posicion en el vector para luego poder editar el billboard
	 */
	int AddBillboard(TOEvector3df position, std::string text, float charSize = 0.2f, std::string texture = "");
	
	/**
	 * @brief	- Cambia el texto del billboard	 
	 * 
	 * @param 	- text - Cadena de texto a poner 
	 * @param 	- id - Posicion del billboard en el vector
	 */
	void SetBillboardText(std::string text, int id = 0);

	/**
	 * @brief	- Cambia la posicion del billboard 
	 * 
	 * @param 	- position - Posicion a poner
	 * @param 	- id - Posicion del billboard en el vector
	 */
	void SetBillboardPosition(TOEvector3df position, int id = 0);

	/**
	 * @brief	- Cambia el tamanyo del billboard 
	 * 
	 * @param 	- charSize - Nuevo tamanyo a poner 
	 * @param 	- id - POsicion del billboard en el vector 
	 */
	void SetBillboardSize(float charSize, int id = 0);

	/**
	 * @brief	- Elimina un billboard 
	 * 
	 * @param 	- id - Posicion del billboard en el vector 
	 */
	void DeleteBillboard(int id = 0);

	/**
	 * @brief	- Elimina todos los billboards 
	 */
	void DeleteAllBillboard();

	/**
	 * @brief Sets bounding box of the entity (normally meshes or lights)
	 * 
	 * @param visible 
	 */
	virtual void SetBoundBox(bool visible);


	/**
	 * @brief Change the shader of the Entity
	 * 
	 * @param Shader to change
	 * @param Type of entity to change the shader
	 */
	virtual void SetProgram(SHADERTYPE shader, ENTITYTYPE entity = NONE_ENTITY);

	/**
	 * @brief	- Devuelve el tipo de entidad del nodo 
	 */
	ENTITYTYPE GetEntityType();

protected:
	// All internal nodes of a node
	TNode* m_rotationNode;				// m_rotationNOde - rotation node
	TNode* m_scaleNode;					// m_scaleNode - scale node
	TNode* m_positionNode;				// m_postionNode - position node
	TNode* m_entityNode;				// m_entityNode - entity node (light, camera, mesh, animation, particles)
	
	std::vector<TFText*> m_billboards;	// m_billboards - Vector of billboards of the TFNode
	std::vector<TFNode*> m_children;	// m_children - Vector of children of the TFNode
	TFNode* m_parent;					// m_parent - If Parent is null, this TFNode is attatched to the ROOT NODE
	ENTITYTYPE m_entity; 				// m_entity - Tipo de entidad del nodo

	/**
	 * @brief	- Constructor del TFNode 
	 */
	TFNode();

	/**
	 * @brief	- Destructro del TFNode 
	 */
	virtual ~TFNode();

	/**
	 * @brief 	Elimina los hijos del nodo
	 */
	void DeleteChildren();

	/**
	 * @brief	- Ligamos el nodo pasado por parametros al nodo scale del TFNode actual 
	 * 
	 * @param 	- root - Nodo a ligar 
	 */
	void Attach(TNode* root);

	/**
	 * @brief	- Ligamos el nodo pasado por parametros al nodo scale del TFNode actual, y lo anyadimos el primero 
	 * 
	 * @param 	- root - Nodo a ligar 
	 */
	void AttachFirst(TNode* root);

	/**
	 * @brief	- Devuelve el nodo entidad 
	 */
	TNode* GetEntityNode();

	/**
	 * @brief	- Devuelve el nodo al que se van a ligar los demas TFNodes 
	 */
	virtual TNode* GetConnectionNode();		// Return the node to connect
};

#endif