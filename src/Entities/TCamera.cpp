#include "TCamera.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <iostream>

/*############################################################################################
# NEW/DELETE #################################################################################
############################################################################################*/

TCamera::TCamera(){
}

TCamera::TCamera(bool perspective, float left, float right, float bottom, float top, float near, float far, Program* p){
	m_program = p;
	if(perspective) SetPerspective(left, right, bottom, top, near, far);
	else SetParallel(left, right, bottom, top, near, far);
}

TCamera::~TCamera(){}

/*############################################################################################
# GETTERS/SETTERS ############################################################################
############################################################################################*/

void TCamera::SetPerspective(float left, float right, float bottom, float top, float near, float far){
	SetNear(near); SetFar(far);
	SetLeft(left); SetRight(right);
	SetTop(top); SetBottom(bottom);
	SetPerspective();
}

void TCamera::SetParallel(float left, float right, float bottom, float top, float near, float far){
	SetNear(near); SetFar(far); 
	SetLeft(left); SetRight(right); 
	SetTop(top); SetBottom(bottom);
	SetParallel();
}

void TCamera::SetPerspective(){
	m_perspective = true;
	RecalculateProjectionMatrix();
}

void TCamera::SetParallel(){
	m_perspective = false;
	RecalculateProjectionMatrix();
}

void TCamera::SetNear(float newVal){
	m_near = newVal;
}

float TCamera::GetNear(){
	return(m_near);
}

void TCamera::SetFar(float newVal){
	m_far = newVal;
}

float TCamera::GetFar(){
	return(m_far);
}

void TCamera::SetLeft(float newVal){
	m_left = newVal;
}

float TCamera::GetLeft(){
	return(m_left);
}

void TCamera::SetRight(float newVal){
	m_right = newVal;
}

float TCamera::GetRight(){
	return(m_right);
}

void TCamera::SetTop(float newVal){
	m_top = newVal;
}

float TCamera::GetTop(){
	return(m_top);
}

void TCamera::SetBottom(float newVal){
	m_bottom = newVal;
}

float TCamera::GetBottom(){
	return(m_bottom);
}

glm::mat4 TCamera::GetProjectionMatrix(){
	return(m_projectionMatrix);
}

/*############################################################################################
# OTHERS #####################################################################################
############################################################################################*/

glm::mat4 TCamera::RecalculateProjectionMatrix(){
	if(m_perspective) m_projectionMatrix = CalculatePerspectiveMatrix();
	else m_projectionMatrix = CalculateOrthogonalMatrix();

	SendMatrixToShader();
	return(m_projectionMatrix);
}

glm::mat4 TCamera::CalculatePerspectiveMatrix(){
	return(glm::frustum(m_left, m_right, m_bottom, m_top, m_near, m_far));
}

glm::mat4 TCamera::CalculateOrthogonalMatrix(){
	return(glm::ortho(m_left, m_right, m_bottom, m_top, m_near, m_far));
}

void TCamera::SendMatrixToShader(){
	if (m_program == nullptr)
		std::cout << "EL PROGRAMA\n";

	GLint uniProj = glGetUniformLocation(m_program->GetProgramID(), "ProjectionMatrix");
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(m_projectionMatrix));
}

/*############################################################################################
# BEGIN/END DRAW #############################################################################
############################################################################################*/

void TCamera::BeginDraw(){}

void TCamera::EndDraw(){}