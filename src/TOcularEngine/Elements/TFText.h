#ifndef TFTEXT_H
#define TFTEXT_H

/**
 * @brief Text Entity Facade.
 * 
 * @file TFText.h
 */

#include "TFNode.h"
#include <TOEvector4d.h>

class TFText: public TFNode{
	friend class TFNode;
public:
	/**
	 * @brief	- Cambia la cadena del texto 
	 * 
	 * @param 	- text - Cadena de texto que se va a poner
	 */
	void SetText(std::string text);

	/**
	 * @brief	- Cambia el tamanyo del texto 
	 */
	void SetSize(float charSize);

protected:
	/**
	 * @brief	- Constructor de la clase TFText
	 * 
	 * @param 	- position - Posicion del texto
	 * @param 	- rotation - Rotacion del texto
	 * @param 	- scale - Tamanyo del texto
	 * @param 	- text - Cadena de texto
	 * @param 	- charSize - Tamanyo del caracter
	 * @param 	- texture - Ruta de la textura del mapa de caracteres
	 */
	TFText(
		TOEvector3df position,
		TOEvector3df rotation,
		TOEvector3df scale,
		std::string text,
		float charSize,
		std::string texture
	);

	/**
	 * @brief	- Destructor de la clase TFText 
	 */
	~TFText();
	
};

#endif