#include "TResourceTexture.h"
#include "../Loaders/TTextureLoader.h"
#include <SOIL2/SOIL2.h>
#include <GL/glew.h>

#include <iostream>

TResourceTexture::TResourceTexture(std::string name){
	m_name = name;

	glBindBuffer(GL_TEXTURE_2D, 0);	
	glGenBuffers(1, &m_textureID);

	m_loaded = false;

	LoadFile();
}


TResourceTexture::~TResourceTexture(){
	if(m_loaded) SOIL_free_image_data(m_imageData);	// Liberar el array de datos
	glBindBuffer(GL_TEXTURE_2D, 0);		// |
	glDeleteBuffers(1, &m_textureID);	// | Eliminar el buffer de datos de OpenGL
}

bool TResourceTexture::LoadFile(){
	bool toRet = TTextureLoader::LoadTexture(m_name, &m_imageData, &m_width, &m_height);
	SetLoaded(toRet);

	if(toRet){
		m_loaded = true;
		// Generamos la nueva texgura
		glGenTextures(1, &m_textureID);
		
		// Bindeamos los parametros a nuestra textura de OpenGL
		glBindTexture(GL_TEXTURE_2D, m_textureID);
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_imageData);	// Cargamos nuestros datos en la textura de OpenGL

		// Algunos Parametros de Textura --> https://www.khronos.org/registry/OpenGL-Refpages/es2.0/xhtml/glTexParameter.xml
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Algunos Filtros de Textura --> https://www.khronos.org/registry/OpenGL-Refpages/es2.0/xhtml/glTexParameter.xml
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	return toRet;
}

GLuint TResourceTexture::GetTextureId(){
	return m_textureID;
}

int  TResourceTexture::GetWidth(){
	return m_width;
}
int  TResourceTexture::GetHeight(){
	return m_height;
}

std::string TResourceTexture::GetTexturePath(){
	return m_name;
}
