#ifndef TMESH_H
#define TMESH_H

#include "TEntity.h"
#include <GL/glew.h>
#include <vector>
#include "../Resources/Program.h"
#include "./../TResourceManager.h"
#include "./../Resources/TResourceMesh.h"
#include "./../Resources/TResourceTexture.h"

class TMesh: public TEntity{
public:
	TMesh();
	~TMesh();

	void SetProgram(Program* prog);
	void BeginDraw();
	void EndDraw();

private:

	Program* 	m_program;

	TResourceMesh* 		m_mesh;
	TResourceTexture* 	m_texture;
	
	/**
	 * @brief Sends shader all needed information
	 * 
	*/
	void SendShaderData();
};

#endif