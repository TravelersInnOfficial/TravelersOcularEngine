#ifndef TPORTAL_H
#define TPORTAL_H

/**
 * @brief TPortal joins 2 TRooms and will clip everthing 
 * 		  behind the portal if its close.
 * 
 * @file TPortal.h
 */

#include <glm/gtc/type_ptr.hpp>

class TRoom;

class TPortal{
public:
	/**
	 * @brief	- Constructor del portal 
	 * 
	 * @param 	- first - Primera habitacion del portal
	 * @param 	- second - Segunda habitacion del portal
	 * @param 	- size - Tamanyo del portal
	 * @param 	- center - Centro del portal
	 * @param 	- rot - Rotacion del portal
	 */
	TPortal(TRoom* first, TRoom* second, glm::vec3 size, glm::vec3 center, glm::vec3 rot);
	
	/**
	 * @brief	- Destructor del portal 
	 */
	~TPortal();

	/**
	 * @brief	- Comprobamos la visibilidad del portal en la pantalla 
	 *
	 * @return 	- bool - El portal se encuentra dentro de la pantalla
	 */
	bool CheckVisibility();

	/**
	 * @brief	 - Comprobamos la visibilidad de un punto dentro de la pantalla
	 * 
	 * @param 	- point - Punto a comprobar
	 * @param 	- upDown - Numero de puntos que se han salido por arribo o debajo
	 * @param 	- leftRight - Numero de puntos que se han salido por los lados
	 * @param 	- nearFar - Numero de puntos que se han salido por el near o far
	 */
	void CheckVisibility(glm::vec4 point, int* upDown, int* leftRight, int* nearFar);
	
	/**
	 * @brief	- Calcula la matriz de transformacion del portal en funcion del tamanyo, centro y rotacion 
	 */
	void CalculateTransform();

	/**
	 * @brief	- Llama al draw de la segunda habitacion 
	 */	
	void DrawSecondRoom();

	/**
	 * @brief	- Activa o desactiva el portal 
	 * 
	 * @param 	- visible - Des/activacion del portal 
	 */
	void SetVisible(bool visible);

	/**
	 * @brief	- Cambia el tamanyo del portal  
	 */
	void SetSize(glm::vec3 size);

	/**
	 * @brief	- Cambia el centro del portal 
	 */
	void SetCenter(glm::vec3 center);

	/**
	 * @brief	- Cambia la rotacion del portal 
	 */
	void SetRotation(glm::vec3 rot);

	/**
	 * @brief	- Devuelve la visibilidad del portal 
	 */
	bool GetVisible();

private:
	/**
	 * @brief	- Devuelve el signo del valor pasado por parametros 
	 * 				Los valores iguales o mayores que 0 devuelven un 1, en caso contrario un -1
	 *
	 * @return 	- int - Signo del valor
	 */
	int Sign(int v);

	bool m_visible;				// m_visible - Si el portal esta activado

	// 1 -> 2
	TRoom* m_firstConnection;	// m_firstConnection - La primera habitacion del portal
	TRoom* m_secondConnection;	// m_secondConnection - La segunda habitacion del portal

	// Forma del portal
	glm::mat4 m_transform;		// m_transform - Matriz transformacion del portal
	glm::vec3 m_size;			// m_size - Tamanyo del portal
	glm::vec3 m_center;			// m_center - Centro del portal
	glm::vec3 m_rotation;		// m_rotation - Rotacion del portal

	float m_limits[4]; 			// m_limits - Los limites de clipping del portal
								// MaxX MinX MaxY MinY

	/**
	 * @brief	- Resetea los limites del clipping del portal por los de por defecto 
	 */
	void PrepareLimits();

	/**
	 * @brief	- Alteramos los limites de clipping de las entidades 
	 */
	void ChangeEntityClipping();

	/**
	 * @brief	- Pintamos la caja que forma el portal de color verde 
	 */
	void DrawDebug();
};

#endif
