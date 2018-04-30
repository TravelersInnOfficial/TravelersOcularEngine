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

	/**
	 * @brief Changes all mesh of this mesh 
	 * 
	 * @param meshPath: Path to mesh from executable
	 */
	void LoadMesh(std::string meshPath = "");
	/**
	 * @brief Changes texture of this mesh
	 * 
	 * @param texturePath: Path to texture from executable
	 */
	void ChangeTexture(std::string texturePath = "");

	void ChangeSpecularMap(std::string texturePath = "");

	/**
	 * @brief Shows or hide mesh bounding box
	 * 
	 * @param visible: visibility of bounding box 
	 */
	void SetBBVisibility(bool visible);

	void SetTextureScale(float valueX, float valueY);

protected:

	TResourceMesh* 		m_mesh;
	TResourceTexture* 	m_texture;
	TResourceTexture*	m_specularMap;
	TResourceMaterial* 	m_material;

	bool m_visibleBB;
	bool m_drawingShadows;

	float m_textureScaleX;
	float m_textureScaleY;

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
	 * @brief Check if this is mesh is clipped from camera so doesn't has to be drawn
	 * 
	 * @return true: is inside the viewport
	 * @return false: is outside the viewport 
	 */
	virtual	bool CheckClipping() override;
	
	/**
	 * @brief Check if this is mesh is occluded by other object so doesn't has to be drawn
	 * 
	 * @return true: is visible in the viewport
	 * @return false:  is totally occluded
	 */
	virtual	bool CheckOcclusion();

private:
	int Sign(int v);
};

#endif