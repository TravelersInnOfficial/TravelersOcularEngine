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

	virtual void BeginDraw() override;
	virtual void EndDraw() override;
	virtual void DrawShadow() override;

	void LoadMesh(std::string meshPath = "");
	void ChangeTexture(std::string texturePath = "");
	void SetBBVisibility(bool visible);

protected:

	TResourceMesh* 		m_mesh;
	TResourceTexture* 	m_texture;
	TResourceMaterial* 	m_material;
	bool m_visibleBB;
	bool m_drawingShadows;

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

	/**
	 * @brief 
	 * 
	 * @return true 
	 * @return false 
	 */
	virtual	bool CheckClipping() override;
	
	/**
	 * @brief 
	 * 
	 * @return true 
	 * @return false 
	 */
	virtual	bool CheckOclusion();

private:
	int Sign(int v);
};

#endif