#ifndef TTEXT_H
#define TTEXT_H

#include "TEntity.h"
#include "./../Resources/TResourceTexture.h"
#include "../Resources/Program.h"

#include <iostream>

class TText: public TEntity{
public:
	TText(std::string text = "", std::string texture = "");
	~TText();

	void BeginDraw();
	void EndDraw();

	void ChangeText(std::string text);

private:
	void LoadText(std::string text);
	void SendShaderData();

	TResourceTexture* 	m_texture;	// Imagen con todas las letras de la tipografia
	std::string 		m_text;		// Texto de la entidad

	int 				m_size;		// Number of vertex
	GLuint				m_uvbo;		// Buffer de uvs
	GLuint				m_vbo;		// Buffer de vertices
};

#endif