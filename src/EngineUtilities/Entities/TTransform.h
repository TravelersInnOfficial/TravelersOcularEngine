#ifndef TTRANSFORM_H
#define TTRANSFORM_H

/**
 * @brief Transformation of each Entity in scene tree.
 * 
 * @file TTransform.h
 */

#include "./TEntity.h"
#include <glm/mat4x4.hpp>

class TTransform: public TEntity{
public:
	/**
	 * @brief	- Constructor de la clase TTransform 
	 * 				en este se carga la matriz identidad
	 */
	TTransform();

	/**
	 * @brief	- Destructor de la clase TTransform 
					Al no tener variables que eliminar esta vacio
	 */
	~TTransform();

	/**
	 * @brief	- Carga la matriz identidad en la transformacion 
	 */
	void 	Identity();							

	/**
	 * @brief	- Carga la matriz pasado por parametros 
	 * 
	 * @param 	- newMatrix - Matriz a copiar
	 */	
	void 	Load(glm::mat4 newMatrix);			

	/**
	 * @brief	- Transpone la matriz transformacion 
	 */
	void 	Transpose();							

	/**
	 * @brief	- Invierte la matriz transformacion 
	 */
	void 	Inverse();								
	
	/**
	 * @brief	- Aplicamos una operacion de translacion a la transformacion 
	 * 
	 * @param 	- X - Translacion en el eje X
	 * @param 	- Y - Translacion en el eje Y 
	 * @param 	- Z - Translacion en el eje Z 
	 */
	void 	Translate(float X, float Y, float Z);

	/**
	 * @brief	- Aplicamos una operacion de rotacion a la transformacion
	 * 
	 * @param 	- X - Rotacion en el eje X 
	 * @param 	- Y - Rotacion en el eje Y 
	 * @param 	- Z - Rotacion en el eje Z 
	 */
	void	Rotate(float X, float Y, float Z);		

	/**
	 * @brief 	- Aplicamos una operacion de rotacion a la transformacion respecto a un vector
	 * 
	 * @param 	- X - Variable X del vector 
	 * @param 	- Y - Variable Y del vector
	 * @param 	- Z - Variable Z del vector 
	 * @param 	- W - Grados a rotar respecto al vector
	 */
	void 	Rotate(float X, float Y, float Z, float W);		

	/**
	 * @brief 	- Aplicamos una operacion de escalado a la transformacion 
	 * 
	 * @param 	- X - Escalado en X
	 * @param 	- Y - Escalado en Y
	 * @param 	- Z - Escalado en Z
	 */
	void 	Scale(float X, float Y, float Z);					

	/**
	 * @brief	- Empezamos a pintar la transformacion
	 * 				Apilamos una nueva transformacion en la pila 
	 */
	void 	BeginDraw();					

	/**
	 * @brief	- Acabamos de pintar la transformacion
	 * 				Desapilamos una transformacion de la pila 
	 */		
	void 	EndDraw();	

	/**
	 * @brief 	- Pintamos por consola la matriz transformacion
	 */					
	void 	PrintMatrix();

	/**
	 * @brief 	- Pintamos por consola la matriz pasada por parametros
	 * 
	 * @param  	- matrix - Matriz a pintar
	 */
	void 	PrintMatrix(glm::mat4 matrix);

	/**
	 * @brief 	- Devolvemos la matriz transformacion
	 * 
	 * @return 	- glm::mat4 - Matriz transformacion de la clase
	 */
	glm::mat4 GetTransform();

private:
	glm::mat4 m_matrix;		// m_matix - Matriz de transformacion de 4x4
};

#endif