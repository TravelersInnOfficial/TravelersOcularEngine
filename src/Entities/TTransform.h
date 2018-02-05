#ifndef TTRANSFORM_H
#define TTRANSFORM_H

#include "./TEntity.h"
//#include <glm/mat4x4.hpp> // glm::mat4
//#include <glm/vec3.hpp> // glm::mat4
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

class TTransform: public TEntity{
public:
	TTransform();
	~TTransform();

	void 	Identity();								// Cargar la matriz identidad
	void 	Load(glm::mat4 newMatrix);				// Cargar la matriz pasada por parametros
	void 	Transpose();							// Transponer la matriz
	//...
	void 	Translate(float X, float Y, float Z);	// Mover la matriz...
	void 	Rotate(float, float, float, float);		// Rotar la matriz..

	void 	BeginDraw();							// Empezar a pintar la transformacion
	void 	EndDraw();								// Acabar de pintar la transformacion
	void 	PrintMatrix();

private:
	glm::mat4 m_matrix;								// Matriz de transformacion de 4x4
};

#endif