#ifndef TMESH_H
#define TMESH_H

#include "TEntity.h"
#include "../Resources/Program.h"
#include "./../TResourceManager.h"
#include "./../Resources/TResourceMesh.h"
#include "./../Resources/TResourceTexture.h"

class TMesh: public TEntity{
public:
	TMesh(std::string meshPath = "", std::string texturePath = "");
	virtual ~TMesh();

	virtual void BeginDraw();
	virtual void EndDraw();
	virtual	bool CheckClipping();

	void LoadMesh(std::string meshPath = "");
	void ChangeTexture(std::string texturePath = "");
	void SetBBVisibility(bool visible);

protected:

	TResourceMesh* 		m_mesh;
	TResourceTexture* 	m_texture;
	TResourceMaterial* 	m_material;
	bool m_visibleBB;

	/**
	 * @brief Sends shader all needed information
	 * 
	*/
	void SendShaderData();

	/**
	 * @brief Draws bounding box of the mesh
	 * 
	 */
	void DrawBoundingBox();	

	int Sign(float n);
};

#endif