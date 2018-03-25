#include "./TTransform.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iostream>

TTransform::TTransform(){
	m_matrix = glm::mat4(1.0f);
	m_program = STANDARD_SHADER;
}

TTransform::~TTransform(){}

void TTransform::Identity(){
	m_matrix = glm::mat4(1.0f);
}


#include <glm/gtx/string_cast.hpp>
void TTransform::Load(glm::mat4 matrix){
	m_matrix = matrix;
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
	glm::quat axisX = glm::angleAxis(glm::radians(X), glm::vec3(1,0,0));
	glm::quat axisY = glm::angleAxis(glm::radians(Y), glm::vec3(0,1,0));
	glm::quat axisZ = glm::angleAxis(glm::radians(Z), glm::vec3(0,0,1));


	glm::quat crossed = glm::cross(axisZ, axisY);

 	glm::mat4 final1 = glm::toMat4(crossed);
 	glm::mat4 final2 = glm::toMat4(axisX);

 	m_matrix = final1 * m_matrix * final2;

	//Rotate(1, 0, 0, X);
	//Rotate(0, 1, 0, Y);
	//Rotate(0, 0, 1, Z);
}

void TTransform::Scale(float X, float Y, float Z){
	m_matrix = glm::scale(m_matrix, glm::vec3(X,Y,Z));
}

void TTransform::BeginDraw(){
	// Apilar la multiplicacion de la matriz de la transformacion y la matriz actual
	m_stack.push(m_matrix * m_stack.top());
	//PrintMatrix(m_stack.top());
}

void TTransform::EndDraw(){
	// Desapilar matriz y ponerla como actual
	m_stack.pop();
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
