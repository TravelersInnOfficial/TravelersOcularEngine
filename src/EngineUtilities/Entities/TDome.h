#ifndef TDOME_H
#define TDOME_H

/**
 * @brief SkyDome of TOE, will be rendered before every node in scene.
 * 
 * @file TDome.h
 */

#include "TMesh.h"

class TDome: public TMesh{
public:
	/**
	 * @brief	- Contructor del SkyDome  
	 * 
	 * @param 	- texturePath - ruta a la textura que va a mostrar
	 */
	TDome(std::string texturePath = "");

	/**
	 * @brief	- Destructor del dome, utiliza el del padre para vaciar sus buffers
	 */
	~TDome();

	/**
	 * @brief	- Empezamos a pintar el dome con el ZBuffer desactivado 
	 */
	virtual void BeginDraw() override;

	/**
	 * @brief	- Acabamos de pintar el dome 
	 */
	virtual void EndDraw() override;

	/**
	 * @brief	- Marcamos a true que se han pintado sombras al no querer que el dome las emita 
	 */
	virtual void DrawShadow() override;

private:
	/**
	 * @brief Send to shader all vertex and texture
	 */
	void SendShaderData();

	bool m_drawingShadows;	// m_drawingShadows - Las sombras se han pintado o no

};

#endif