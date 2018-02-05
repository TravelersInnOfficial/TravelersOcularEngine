#include "TCamera.h"

/*############################################################################################
# NEW/DELETE #################################################################################
############################################################################################*/

TCamera::TCamera(bool m_perspective, float m_near, float m_far, float m_left, float m_right, float m_top, float m_bottom){
	if(m_perspective) SetPerspectiva(m_near, m_far, m_left, m_right, m_top, m_bottom);
	else SetParalela(m_near, m_far, m_left, m_right, m_top, m_bottom);
}

TCamera::~TCamera(){}

/*############################################################################################
# GETTERS/SETTERS ############################################################################
############################################################################################*/

void TCamera::SetPerspectiva(float m_near, float m_far, float m_left, float m_right, float m_top, float m_bottom){
	SetNear(m_near); SetFar(m_far); SetLeft(m_left); SetRight(m_right); SetTop(m_top); SetBottom(m_bottom);
	SetPerspectiva();
}

void TCamera::SetParalela(float m_near, float m_far, float m_left, float m_right, float m_top, float m_bottom){
	SetNear(m_near); SetFar(m_far); SetLeft(m_left); SetRight(m_right); SetTop(m_top); SetBottom(m_bottom);
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
	this->m_near = newVal;
}

float TCamera::GetNear(){
	return(this->m_near);
}

void TCamera::SetFar(float newVal){
	this->m_far = newVal;
}

float TCamera::GetFar(){
	return(this->m_far);
}

void TCamera::SetLeft(float newVal){
	this->m_left = newVal;
}

float TCamera::GetLeft(){
	return(this->m_left);
}

void TCamera::SetRight(float newVal){
	this->m_right = newVal;
}

float TCamera::GetRight(){
	return(this->m_right);
}

void TCamera::SetTop(float newVal){
	this->m_top = newVal;
}

float TCamera::GetTop(){
	return(this->m_top);
}

void TCamera::SetBottom(float newVal){
	this->m_bottom = newVal;
}

float TCamera::GetBottom(){
	return(this->m_bottom);
}

glm::mat4 TCamera::GetProjectionMatrix(){
	return(this->m_projectionMatrix);
}

/*############################################################################################
# OTHERS #####################################################################################
############################################################################################*/

glm::mat4 TCamera::RecalculateProjectionMatrix(){
	glm::mat4 projectionMatrix = glm::mat4(1.0f);

	if(this->m_perspective) projectionMatrix = CalculatePerspectiveMatrix();
	else projectionMatrix = CalculateOrthogonalMatrix();

	this->m_projectionMatrix = projectionMatrix;
	return(projectionMatrix);
}

glm::mat4 TCamera::CalculatePerspectiveMatrix(){
	glm::mat4 projectionMatrix = glm::mat4(1.0f);
	
	// Specifies the field of view angle (in degrees) in the y direction.
	float fovy = 90;
	
	float w = m_right - m_left;
	float h = m_top - m_bottom;
	float aspect = w/h;

	projectionMatrix = glm::perspective (fovy, aspect, m_near, m_far);
	return(projectionMatrix);
}

glm::mat4 TCamera::CalculateOrthogonalMatrix(){
	return(glm::ortho(m_left, m_right, m_bottom, m_top, m_near, m_far));
}

/*############################################################################################
# BEGIN/END DRAW #############################################################################
############################################################################################*/

void TCamera::TCamera::BeginDraw(){}

void TCamera::TCamera::EndDraw(){}