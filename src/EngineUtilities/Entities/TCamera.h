#ifndef TCAMERA_H
#define TCAMERA_H

/**
 * @brief Camera Entity that will render its view.
 * 
 * @file TCamera.h
 */

#include "TEntity.h"
#include <glm/mat4x4.hpp>
#include "../Resources/Program.h"

class TCamera: public TEntity{
public:
	/**
	 * @brief	- Constructor de la camara en la que se pasan todas las variables por parametros
	 * 
	 * @param 	- perspective - la camara es perspectiva o ortografica
	 * @param 	- left - valor izquierda de la pantalla
	 * @param 	- right - valor derecho de la pantalla
	 * @param 	- bottom - valor inferior de la pantalla
	 * @param 	- top - valor superior de la pantalla
	 * @param 	- near - valor de cercania de la camara
	 * @param 	- far - valor de lejania de la camara 
	 */
	TCamera	(
				bool perspective = true,
				float left = -0.1f,
				float right = 0.1f,
				float bottom = -0.075f,
				float top = 0.075f,
				float near = 0.1f,
				float far = 500.0f
			);
	~TCamera();

	/**
	 * @brief	- Cambia las variables de la camara y calcula la matriz de proyeccion de esta
	 */
	void SetPerspective(float left, float right, float bottom, float top, float near, float far);
	
	/**
	 * @brief	- Cambia las variables de la camara y calcula la matriz de proyeccion de esta 
	 */
	void SetParallel(float left, float right, float bottom, float top, float near, float far);

	/**
	 * @brief	- Calcula la matriz proyeccion de la camara perspectiva 
	 */
	void SetPerspective();

	/**
	 * @brief	- Calcula la matriz proyeccion de la camara ortogonal
	 */
	void SetParallel();

	/**
	 * @brief	- Devuelve si la camara es ortogonal o perspectiva 
	 * 
	 * @return 	- bool - True: La camara es perspectiva
	 * @return 	- bool - False: La camara es ortogonal
	 */
	bool GetPerspective();

	/**
	 * @brief	- Cambia la variable near de la camara 
	 * 
	 * @param 	- newVal - Nuevo valor near
	 */
	void SetNear(float newVal);

	/**
	 * @brief 	- Devuelve la variable near de la camara 
	 * 
	 * @return 	- float - variable near
	 */
	float GetNear();

	/**
	 * @brief	- Cambia la variable far de la camara 
	 * 
	 * @param 	- newVal - Nuevo valor far 
	 */	
	void SetFar(float newVal);

	/**
	 * @brief	- Devuelve la variable far de la camara 
	 * 
	 * @return	- float - variable far 
	 */
	float GetFar();
	
	/**
	 * @brief	- Cambia la variable left de la camara 
	 * 
	 * @param 	- newVal - Nuevo valor left 
	 */
	void SetLeft(float newVal);

	/**
	 * @brief	- Devuelve la variable left de la camara 
	 * 
	 * @return	- float - variable left 
	 */
	float GetLeft();

	/**
	 * @brief	- Cambia la variable right de la camara 
	 * 
	 * @param 	- newVal - Nuevo valor right 
	 */
	void SetRight(float newVal);

	/**
	 * @brief	- Devuelve la variable right de la camara 
	 * 
	 * @return	- float - variable right 
	 */
	float GetRight();

	/**
	 * @brief	- Cambia la variable top de la camara 
	 * 
	 * @param 	- newVal - Nuevo valor top 
	 */
	void SetTop(float newVal);

	/**
	 * @brief	- Devuelve la variable top de la camara 
	 * 
	 * @return	- float - variable top 
	 */
	float GetTop();

	/**
	 * @brief	- Cambia la variable bottom de la camara 
	 * 
	 * @param 	- newVal - Nuevo valor bottom 
	 */
	void SetBottom(float newVal);

	/**
	 * @brief	- Devuelve la variable bottom de la camara 
	 * 
	 * @return	- float - variable bottom 
	 */
	float GetBottom();

	/**
	 * @brief	- Devuelve la matriz proyeccion de la camara 
	 * 
	 * @return	- glm::mat4 - Matriz proyeccion 
	 */
	glm::mat4 GetProjectionMatrix();

	/**
	 * @brief	- Recalcula la matriz proyeccion a traves de las variables de la camara 
	 */
	void RecalculateProjectionMatrix();
	
	SHADERTYPE m_program;	// m_program - Shader de la camara

	/**
	 * @brief	- Metodo de iniciar a pintar (Vacio) 
	 */
	void BeginDraw();

	/**
	 * @brief	- Metodo de acabar de pintar (Vacio) 
	 */
	void EndDraw();

private:
	bool m_perspective;				// m_perspective - Si es perspetiva o ortogonal

	float m_near, m_far;			// 
	float m_left, m_right;			//
	float m_top, m_bottom;			// Variables para calcular la matriz proyeccion de la camara

	glm::mat4 m_projectionMatrix;	// m_projectionMatrix - Matriz proyeccion de la camara

	/**
	 * @brief	- Calculamos la matriz proyeccion de una camara perspectiva 
	 * 
	 * @return 	- glm::mat4 - Matriz proyeccion correspondiente
	 */
	glm::mat4 CalculatePerspectiveMatrix();	

	/**
	 * @brief	- Calculamos la matriz proyeccion de una camara ortogonal 
	 * 
	 * @return	- glm::mat4 - Matriz proyeccion correspondiente 
	 */
	glm::mat4 CalculateOrthogonalMatrix();

};

#endif