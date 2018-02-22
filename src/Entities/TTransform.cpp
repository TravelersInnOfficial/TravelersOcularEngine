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

void TTransform::Inverse(){
	m_matrix = glm::inverse(m_matrix);
}

void TTransform::Translate(float X, float Y, float Z){
	m_matrix = glm::translate(m_matrix, glm::vec3(X,Y,Z));
}

void TTransform::Rotate(float X, float Y, float Z, float W){
	m_matrix = glm::rotate(m_matrix, glm::radians(W), glm::vec3(X,Y,Z));
}

void TTransform::Rotate(float X, float Y, float Z){
	Rotate(1, 0, 0, X);
	Rotate(0, 1, 0, Y);
	Rotate(0, 0, 1, Z);
}

void TTransform::Scale(float X, float Y, float Z){
	m_matrix = glm::scale(m_matrix, glm::vec3(X,Y,Z));
}

void TTransform::BeginDraw(){
	// Apilar la multiplicacion de la matriz de la transformacion y la matriz actual
	m_stack.push(m_stack.top() * m_matrix);
	//PrintMatrix(m_stack.top());
}

void TTransform::EndDraw(){
	// Desapilar matriz y ponerla como actual
	m_stack.pop();
	//PrintMatrix(m_stack.top());
}

void TTransform::PrintMatrix(glm::mat4 mat){
	for(int i= 0; i<4; i++){
		for(int j= 0; j<4; j++){
			std::cout<<mat[i][j] << "  "; 
		}
		std::cout<<"\n";
	}
	std::cout<<"\n";
}

void TTransform::PrintMatrix(){
	for(int i= 0; i<4; i++){
		for(int j= 0; j<4; j++)
			std::cout<<m_matrix[i][j] << "  ";
		std::cout<<"\n";
	}
	std::cout<<"\n";
}

glm::mat4 TTransform::GetTransform(){
	return m_matrix;
}
