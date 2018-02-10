#include "TCamera.h"

/*############################################################################################
# NEW/DELETE #################################################################################
############################################################################################*/

TCamera::TCamera(bool perspective, float near, float far, float left, float right, float top, float bottom){
	if(perspective) SetPerspectiva(near, far, left, right, top, bottom);
	else SetParalela(near, far, left, right, top, bottom);
}

TCamera::~TCamera(){}

/*############################################################################################
# GETTERS/SETTERS ############################################################################
############################################################################################*/

void TCamera::SetPerspectiva(float near, float far, float left, float right, float top, float bottom){
	SetNear(near); SetFar(far); SetLeft(left); SetRight(right); SetTop(top); SetBottom(bottom);
	SetPerspectiva();
}

void TCamera::SetParalela(float near, float far, float left, float right, float top, float bottom){
	SetNear(near); SetFar(far); SetLeft(left); SetRight(right); SetTop(top); SetBottom(bottom);
	SetParalela();
}

void TCamera::SetPerspectiva(){
	m_perspective = true;
	RecalculateProjectionMatrix();
}

void TCamera::SetParalela(){
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
	glm::mat4 projectionMatrix = glm::mat4(1.0f);

	if(m_perspective) projectionMatrix = CalculatePerspectiveMatrix();
	else projectionMatrix = CalculateOrthogonalMatrix();

	m_projectionMatrix = projectionMatrix;
	return(projectionMatrix);
}

glm::mat4 TCamera::CalculatePerspectiveMatrix(){
	return(glm::frustum(m_left, m_right, m_bottom, m_top, m_near, m_far));
}

glm::mat4 TCamera::CalculateOrthogonalMatrix(){
	return(glm::ortho(m_left, m_right, m_bottom, m_top, m_near, m_far));
}

/*############################################################################################
# BEGIN/END DRAW #############################################################################
############################################################################################*/

void TCamera::BeginDraw(){}

void TCamera::EndDraw(){}