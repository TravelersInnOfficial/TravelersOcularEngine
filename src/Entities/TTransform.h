#ifndef TTRANSFORM_H
#define TTRANSFORM_H

#include "./TEntity.h"

#include <iostream>

class TTransform: public TEntity{
public:
	TTransform();
	~TTransform();

	void 	Identity();								// Cargar la matriz identidad
	void 	Load(float matrix[4][4]);				// Cargar la matriz pasada por parametros
	void 	Transpose();							// Transponer la matriz
	//...
	void 	Translate(float X, float Y, float Z);	// Mover la matriz...
	void 	Rotate(float, float, float, float);		// Rotar la matriz..

	void 	BeginDraw();							// Empezar a pintar la transformacion
	void 	EndDraw();								// Acabar de pintar la transformacion
private:
	float 	m_matrix[4][4];	// Matriz de transformacion de 4x4
};

#endif