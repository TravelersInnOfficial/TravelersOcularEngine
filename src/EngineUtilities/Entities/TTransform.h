#ifndef TTRANSFORM_H
#define TTRANSFORM_H

#include "./TEntity.h"
#include <glm/mat4x4.hpp>

class TTransform: public TEntity{
public:
	TTransform();
	~TTransform();

	void 	Identity();								// Cargar la matriz identidad
	void 	Load(glm::mat4 newMatrix);				// Cargar la matriz pasada por parametros
	void 	Transpose();							// Transponer la matriz
	void 	Inverse();								// Invertir la matriz
	
	void 	Translate(float X, float Y, float Z);		// Mover la matriz
	void	Rotate(float X, float Y, float Z);			// Rotar la matriz (TODOS LOS EJES)
	void 	Rotate(float, float, float, float);			// Rotar la matriz (SOLO UN EJE)
	void 	Scale(float, float, float);					// Escalar la matriz

	void 	BeginDraw();							// Empezar a pintar la transformacion
	void 	EndDraw();								// Acabar de pintar la transformacion
	void 	PrintMatrix();
	void 	PrintMatrix(glm::mat4);
	glm::mat4 GetTransform();

private:
	glm::mat4 m_matrix;								// Matriz de transformacion de 4x4
};

#endif