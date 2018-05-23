#ifndef TMESH_H
#define TMESH_H

/**
 * @brief Mesh Entity that will draw all polygons.
 * 
 * @file TMesh.h
 */

#include "TEntity.h"
#include "../Resources/Program.h"
#include "./../TResourceManager.h"
#include "./../Resources/TResourceMesh.h"
#include "./../Resources/TResourceTexture.h"

class TMesh: public TEntity{
public:

	/**
	 * @brief	- Constructor del mesh 
	 *
	 * @param	- meshPath - ruta al mesh que va a mostrar
	 * @param 	- texturePath - ruta a la textura que va a utilizar
	 */
	TMesh(std::string meshPath = "", std::string texturePath = "");
	
	/**
	 * @brief	- Destructor virtual del mesh, las variables dinamicas que tiene el mesh
	 * 				se eliminan en el gesto de recursos 
	 */
	virtual ~TMesh();

	/**
	 * @brief	- Metodo en el que se pinta el mesh enviando todos los datos a los shaders
	 */
	virtual void BeginDraw() override;

	/**
	 * @brief	- Metodo de dejar de acabar de pintar el mesh, en este metodo se resetean las variables necesarias 
	 */
	virtual void EndDraw() override;

	/**
	 * @brief	- Pinta el mesh para calcular las sombras que este hace
	 */
	virtual void DrawShadow() override;

	/**
	 * @brief	- Cambia el mesh que se pinta
	 * 
	 * @param	- meshPath - Ruta al mesh
	 */
	void LoadMesh(std::string meshPath = "");

	/**
	 * @brief 	- Cambia la textura que utiliza el mesh
	 * 
	 * @param 	- texturePath - Ruta a la textura
	 */
	void ChangeTexture(std::string texturePath = "");

	/**
	 * @brief 	- Cambia el mapa de especulares que utiliza el mesh
	 * 
	 * @param 	- texturePath - Ruta al mapa de especulares
	 */
	void ChangeSpecularMap(std::string texturePath = "");

	/**
	 * @brief 	- Cambia el mapa de normales que utiliza el mesh
	 * 
	 * @param 	- texturePath - Ruta al mapa de normales 
	 */
	void ChangeBumpMap(std::string texturePath = "");

	/**
	 * @brief 	- Muestra o esconde el bounding box del mesh
	 * 
	 * @param 	- visible - Visibiliddad del bounding box
	 */
	void SetBBVisibility(bool visible);

	/**
	 * @brief	- Cambia el escalado de la textura  
	 * 
	 * @param 	- valueX - Escalado en X de la textura 
	 * @param 	- valueY - Escalado en Y de la textura
	 */
	void SetTextureScale(float valueX, float valueY);

protected:

	unsigned int 		m_frameDrawed;	// m_frameDrawed - Ultimo frame en el que se ha pintado
	TResourceMesh* 		m_mesh;			// m_mesh - Recurso de mesh a pintar
	TResourceTexture* 	m_texture;		// m_texture - Recurso textura a utilizar
	TResourceTexture*	m_specularMap;	// m_specularMap - Mapa de especulares a utilizar
	TResourceTexture*	m_bumpMap;		// m_bumpMap - Mapa de normales a utilizar
	TResourceMaterial* 	m_material;		// m_material - Material del mesh

	bool m_visibleBB;
	bool m_drawingShadows;

	float m_textureScaleX;
	float m_textureScaleY;

	/**
	 * @brief	- Envia a los shaders toda la informacion necesaria 
	 * 
	*/
	void SendShaderData();

	/**
	 * @brief	- Dibuja el bounding box del mesh 
	 * 
	 */
	void DrawBoundingBox();	

	/**
	 * @brief	- Comprueba si los 8 puntos del bounding box del objeo se encuentran dentro de la pantalla
	 *				para sabe si puede dejar de pintarse o no   
	 * 
	 * @return 	- bool - True: Se encuentra dentro de la pantall
	 * @return 	- bool - False: Esta fuera de la pantalla 
	 */
	virtual	bool CheckClipping() override;
	
	/**
	 * @brief 	- Comprueba si un objeto esta ocluido por otro para poder dejar de pintarlo
	 * 
	 * @return 	- bool - True: El objeto es visible
	 * @return 	- bool - False: El objeto esta ocluido
	 */
	virtual	bool CheckOcclusion();

private:
	/**
	 * @brief	- Devuelve el signo del valor pasado por parametros 
	 * 				Los valores mayores o igual a 0 devolveran un 1, mientras que los demas un -1
	 * 
	 * @param 	- value - Valor del que sacar el signo
	 * @return 	- int - Signo del valor
	 */
	int Sign(int value);
};

#endif