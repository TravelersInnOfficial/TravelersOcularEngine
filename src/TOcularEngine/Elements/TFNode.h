#ifndef TFNODE_H
#define TFNODE_H

#include <TOEvector3d.h>
#include <TColor.h>
#include <glm/gtx/matrix_decompose.hpp>
#include "./../../EngineUtilities/TNode.h"
#include "./../../EngineUtilities/Entities/TTransform.h"
#include "./../../EngineUtilities/Entities/TMesh.h"
#include "./../../EngineUtilities/Entities/TLight.h"
#include "./../../EngineUtilities/Entities/TCamera.h"

class SceneManager;

class TFNode{
	friend class SceneManager;

public:
	void SetTranslate(toe::core::TOEvector3df translation);		// Sets the rotation of the Node
	void SetRotation(toe::core::TOEvector3df rotation);			// Sets the position of the Node
	void SetScale(toe::core::TOEvector3df scale);				// Sets the scale of the Node

	void Translate(toe::core::TOEvector3df translation);		// Adds the position to the current position
	void Rotate(toe::core::TOEvector3df rotation);				// Adds the rotation to the current rotation
	void Scale(toe::core::TOEvector3df scale);					// Adds the scale to the current scale

	toe::core::TOEvector3df GetTranslation();	// Returns the rotation of the Node
	toe::core::TOEvector3df GetRotation();		// Returns the position of the Node
	toe::core::TOEvector3df GetScale();			// Returns the scale of the Node

	void AddChild(TFNode* children);			// Adds a Children to the TFNode
	void RemoveChild(TFNode* children);			// Removes Children from the TFNode
	void SetParent(TFNode* parent = nullptr);	// Adds a Parent to the TFNode


	/*
	 * SET PARENT:
	 * 		1.- Compruebo si mi padre es NULL
	 * 			1.1.- Si mi padre no es NULL...
	 * 				1.1.1.- Si es el mismo, no hago nada
	 * 				1.1.2.- Si es otro lo pongo a NULL y le hago un RemoveChild de mi mismo
	 * 		2.- Ahora añado al nuevo nodo como mi padre
	 * 		3.- Vinculo mi TNode Posicion a su TNode Rotacion como hijo (Mi posicion tiene de hijo su rotacion con Attatch)
	 * 		4.- Accedo a mi nuevo padre y le hago un AddChild, metiendome a mi mismo
	 * 
	 * 
	 * SET PARENT VACIO:
	 * 	 	1.- Compruebo si mi padre es NULL
	 *			1.1.- Si mi padre es NULL no hago nada
	 * 		1.- Desvinculo el TNode Rotacion del TNode Posicion del padre y se lo vinculo al ROOT (Con Attatch)
	 *		2.- Pongo a mi Parent a NULL
	 * 		3.- Cojo a mi antiguo padre y le hago un Remove Children de mi
	 * 
	 * 
	 * ADD CHILD:
	 * 		1.- Compruebo si no lo tenia ya en mi vector
	 * 			1.1.- Si me tenia no hago nada
	 * 		2.- Me meto en el vector de hijos
	 * 		4.- Hago un SetParent del TFNode hijo con mi TFNode
	 * 
	 * 
	 * REMOVE CHILD:
	 * 		1.- Compruebo si lo tengo en mi vector
	 * 			1.1.- Si lo tengo, le hago un SetParent vacío
	 * 			1.2.- Si no lo tengo no hago nada
	 */

protected:
	TNode* m_entityNode;
	TNode* m_positionNode;
	TNode* m_rotationNode;
	TNode* m_scaleNode;
	
	std::vector<TFNode*> children;
	TFNode* parent;				// If Parent is null, this TFNode is attatched to the ROOT NODE

	TFNode();
	virtual ~TFNode();
	void DeleteChildren();
	void Attach(TNode* root);	// TNode to be attached to (Rotation will be children to the new TNode)

};

#endif