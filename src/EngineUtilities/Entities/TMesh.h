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

	void LoadMesh(std::string meshPath = "");
	void ChangeTexture(std::string texturePath = "");

protected:

	TResourceMesh* 		m_mesh;
	TResourceTexture* 	m_texture;
	TResourceMaterial* 	m_material;
	
	/**
	 * @brief Sends shader all needed information
	 * 
	*/
	void SendShaderData();
};

#endif