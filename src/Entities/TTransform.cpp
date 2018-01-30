#include "./TTransform.h"

TTransform::TTransform(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			m_matrix[i][j] = 0;		// Creamos la matriz vacia, con todo 0
		}
	}
}

TTransform::~TTransform(){}

void TTransform::Identity(){
	int value = 0;
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			if(i==j){
				value = 1;			// En el caso de que la I y la J coincidan cargamos un 1	
			}else{
				value = 0;			// En caso contrario un 0
			}
			m_matrix[i][j] = value;	// Reseteamos la matriz dejando la matriz identidad
		}
	}
}

void TTransform::Load(float matrix[4][4]){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			m_matrix[i][j] = matrix[i][j];	// Cargamos el valor de la matriz pasado en la propia
		}
	}
}

void TTransform::Transpose(){
	// ----------------------------------------------IMPORTANTE-----------------------
	// Casi seguro que se puede hacer sin utilizar una copia al ser cuadrada
	float copy[4][4];
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			copy[j][i] = m_matrix[j][i];	// Transponemos los valores de la matriz
		}
	}
	Load(copy);
}

void TTransform::Translate(float X, float Y, float Z){
	std::cout<<"Por hacer Translate"<<std::endl;
}

void TTransform::Rotate(float X, float Y, float Z, float W){
	std::cout<<"Por hacer Rotate"<<std::endl;
}

void TTransform::BeginDraw(){
	// Apilar matriz actual
	// Multiplicar la matriz de la transformacion a la matriz actual
}

void TTransform::EndDraw(){
	// Desapilar matriz y ponerla como actual
}						