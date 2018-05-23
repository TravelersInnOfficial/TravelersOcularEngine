#ifndef TTEXT_H
#define TTEXT_H

/**
 * @brief Text that will rotate depending of camera position. AKA Billboard.
 * 
 * @file TText.h
 */

#include "TEntity.h"
#include "./../Resources/TResourceTexture.h"
#include "../Resources/Program.h"

class TText: public TEntity{
public:
	/**
	 * @brief 	- Constructor de la clase texto
	 * 
	 * @param 	- text - Texto a pintar 
	 * @param 	- charSize - Tamanyo de cada caracter
	 * @param 	- texture - Textura de donde pillar los caracteres a pintar
	 */
	TText(std::string text, float charSize, std::string texture);
	
	/**
	 * @brief 	- Destructor de la clase texto, vaciamos y eliminamos los buffers que se utilizan
	 */
	~TText();

	/**
	 * @brief 	- Enviamos la informacion al shader y pintamos el texto
	 */
	virtual void BeginDraw() override;

	/**
	 * @brief 	- Reseteamos las variables requeridas
	 */
	virtual void EndDraw() override;

	/**
	 * @brief	- Al no querer que se pinten sombras sobre el texto el metodo cambia la variable de pintar sombras
	 */
	virtual void DrawShadow() override;

	/**
	 * @brief	- Cambia la cadena de texto que se pinta
	 * 
	 * @param 	- text - Nueva cadena de texto
	 */
	void ChangeText(std::string text);

	/**
	 * @brief	- Cambia el tamanyo de los caracteres de la clase 
	 * 
	 * @param 	- charSize - Nuevo tamanyo de los caracteres
	 */
	void ChangeSize(float charSize);

private:
	/**
	 * @brief	- Generamos los vertices y uvs necesarios para pintar el texto y los cargamos en los buffers
	 * 
	 * @param 	- text - Cadena de texto a pintar
	 */
	void LoadText(std::string text);

	/**
	 * @brief	- Enviamos la informacion al shader 
	 */
	void SendShaderData();

	TResourceTexture* 	m_texture;	// m_texture - Imagen con todas las letras de la tipografia
	std::string 		m_text;		// m_text - Texto de la entidad
	float 				m_charSize;	// m_charSize - Tamanyo de los caracteres

	int 				m_size;		// m_size - Numero de vertices
	GLuint				m_uvbo;		// m_uvbo - Buffer de uvs
	GLuint				m_vbo;		// m_vbo - Buffer de vertices

	bool m_drawingShadows;			// m_drawingShadows - Variable para saber si pintar las sombras
};

#endif