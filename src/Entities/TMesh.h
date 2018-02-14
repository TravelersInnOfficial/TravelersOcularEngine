#ifndef TMESH_H
#define TMESH_H

#include "TEntity.h"
#include <GL/glew.h>
#include <vector>
#include "../Resources/Program.h"

class TMesh: public TEntity{
public:
	TMesh();
	~TMesh();

	//void LoadMesh(TFichero);
	void SetProgram(Program* prog);
	void BeginDraw();
	void EndDraw();

private:

	GLuint   m_vbo;
	GLuint   m_ebo;
	Program* m_program;

	std::vector<GLuint> elements;
	//TResourceMesh* m_mesh
	
	/**
	 * @brief Sends shader all needed information
	 * 
	*/
	void SendShaderData();
};

#endif