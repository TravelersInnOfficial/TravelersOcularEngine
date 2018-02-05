#include "./TTransform.h"

TTransform::TTransform(){
	m_matrix = glm::mat4(1.0f);
}

TTransform::~TTransform(){}

void TTransform::Identity(){
	m_matrix = glm::mat4(1.0f);
}

void TTransform::Load(glm::mat4 matrix){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			m_matrix[i][j] = matrix[i][j];	// Cargamos el valor de la matriz pasado en la propia
		}
	}
}

void TTransform::Transpose(){
	m_matrix = glm::transpose(m_matrix);
}

void TTransform::Translate(float X, float Y, float Z){
	m_matrix = glm::translate(m_matrix, glm::vec3(X,Y,Z));
}

void TTransform::Rotate(float X, float Y, float Z, float W){
	m_matrix = glm::rotate(m_matrix, W, glm::vec3(X,Y,Z));
}

void TTransform::BeginDraw(){
	// Multiplicar la matriz de la transformacion a la matriz actual
	m_matrix = m_stack.top() * m_matrix;

	// Apilar matriz actual
	m_stack.push(m_matrix);
}

void TTransform::EndDraw(){
	// Desapilar matriz y ponerla como actual
	m_stack.pop();
}

void TTransform::PrintMatrix(){
	for(int i= 0; i<4; i++)
	{
		for(int j= 0; j<4; j++)
			std::cout<<m_matrix[i][j] << " ";

		std::cout<<"\n";
	}
}