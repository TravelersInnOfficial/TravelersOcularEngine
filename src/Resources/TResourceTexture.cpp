#include "TResourceTexture.h"
#include "../Loaders/TTextureLoader.h"
#include <SOIL2.h>

TResourceTexture::TResourceTexture(std::string name){
	m_name = name;
	LoadFile();
}

TResourceTexture::TResourceTexture(){
	
}

TResourceTexture::~TResourceTexture(){
	SOIL_free_image_data(&m_imageData); // Liberar el array de datos
	// Liberar el buffer
}

bool TResourceTexture::LoadFile(){
	bool toRet = TTextureLoader::LoadTexture(m_name, &m_imageData, &m_width, &m_height);
	SetLoaded(toRet);

	if(toRet){
		// Preparamos la Textura
		glGenTextures(1, &m_textureID);	// Numero de texturas a generar, array de texturas
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &m_imageData);	// Cargamos nuestros datos en la textura de OpenGL

		// Algunos Parametros de Textura --> https://www.khronos.org/registry/OpenGL-Refpages/es2.0/xhtml/glTexParameter.xml
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Algunos Filtros de Textura --> https://www.khronos.org/registry/OpenGL-Refpages/es2.0/xhtml/glTexParameter.xml
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		// Bindeamos los parametros a nuestra textura de OpenGL
		glBindTexture(GL_TEXTURE_2D, m_textureID);
	}

	return toRet;
}

GLuint TResourceTexture::GetTextureId(){
	return m_textureID;
}