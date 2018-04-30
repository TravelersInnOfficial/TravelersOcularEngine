#ifndef TFNODE_H
#define TFNODE_H

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
	virtual void SetTranslate(TOEvector3df translation);	// Sets the rotation of the Node
	virtual void SetRotation(TOEvector3df rotation);		// Sets the position of the Node
	virtual void SetScale(TOEvector3df scale);			// Sets the scale of the Node

	virtual void Translate(TOEvector3df translation);	// Adds the position to the current position
	virtual void Rotate(TOEvector3df rotation);					// Adds the rotation to the current rotation
	virtual void Scale(TOEvector3df scale);						// Adds the scale to the current scale

	virtual TOEvector3df GetTranslation();	// Returns the rotation of the Node
	virtual TOEvector3df GetRotation();		// Returns the position of the Node
	virtual TOEvector3df GetScale();			// Returns the scale of the Node

	bool AddChild(TFNode* children);			// Adds a Children to the TFNode
	bool RemoveChild(TFNode* children);			// Removes Children from the TFNode
	void RemoveAllChildren();					// Remove ALL Children from the TFNode

	void SetParent(TFNode* parent = nullptr);	// Adds a Parent to the TFNode
	void RemoveParent();						// Removes Parent from the TFNode
	TFNode* GetParent();
	std::vector<TFNode*> GetChildren();

	// Devuelve la posicion en el vector para poder editarlo
	int AddBillboard(TOEvector3df position, std::string text, float charSize = 0.2f, std::string texture = "");
	void SetBillboardText(std::string text, int id = 0);
	void SetBillboardPosition(TOEvector3df position, int id = 0);
	void SetBillboardSize(float charSize, int id = 0);
	void DeleteBillboard(int id = 0);
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

	

protected:
	// All internal nodes of a node
	TNode* m_rotationNode;				// rotation node
	TNode* m_scaleNode;					// scale node
	TNode* m_positionNode;				// position node
	TNode* m_entityNode;				// entity node (light, camera, mesh, animation, particles)
	
	std::vector<TFText*> m_billboards;	// Vector of billboards of the TFNode
	std::vector<TFNode*> m_children;	// Vector of children of the TFNode
	TFNode* m_parent;					// If Parent is null, this TFNode is attatched to the ROOT NODE
	ENTITYTYPE m_entity; 

	TFNode();
	virtual ~TFNode();
	void DeleteChildren();
	void Attach(TNode* root);		// TNode to be attached to (Rotation will be children to the new TNode)	
	void AttachFirst(TNode* root);	// TNode to be attached to (Rotation will be children to the new TNode)	
	TNode* GetEntityNode();			// Return the entity node
	virtual TNode* GetConnectionNode();		// Return the node to connect
};

#endif