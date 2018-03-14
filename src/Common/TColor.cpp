#include "TColor.h"

/*############################################################################################
# NEW/DELETE #################################################################################
############################################################################################*/

TColor::TColor(glm::vec4 rgbaData){
	m_rgba = rgbaData;
}

TColor::~TColor(){}

/*############################################################################################
# GETTERS/SETTERS ############################################################################
############################################################################################*/

void TColor::SetRGBA(glm::vec4 newVal){
	CapValues(newVal);
	m_rgba = newVal;
}

void TColor::SetRGB(glm::vec3 newVal){
	CapValues(newVal);
	m_rgba = glm::vec4(newVal.x, newVal.y, newVal.z, m_rgba.w);
}

void TColor::SetR(float newVal){
	CapValues(newVal);
	m_rgba.x = newVal;
}

void TColor::SetG(float newVal){
	CapValues(newVal);
	m_rgba.y = newVal;
}

void TColor::SetB(float newVal){
	CapValues(newVal);
	m_rgba.z = newVal;
}

void TColor::SetA(float newVal){
	CapValues(newVal);
	m_rgba.w = newVal;
}

void TColor::SetRGBA(float r, float g, float b, float a){
	m_rgba = glm::vec4(r, g, b, a);
}
glm::vec4 TColor::GetRGBA(){
	return(m_rgba);
}

glm::vec3 TColor::GetRGB(){
	return(glm::vec3(m_rgba.x, m_rgba.y, m_rgba.z));
}

float TColor::GetR() const{
	return(m_rgba.x);
}

float TColor::GetG() const{
	return(m_rgba.y);
}

float TColor::GetB() const{
	return(m_rgba.z);
}

float TColor::GetA() const{
	return(m_rgba.w);
}

/*############################################################################################
# OTHERS #####################################################################################
############################################################################################*/

float TColor::CapValues(float valueToCap){
	if(valueToCap < 0.0f) valueToCap = 0.0f;
	if(valueToCap > 1.0f) valueToCap = 1.0f;
	return(valueToCap);
}

glm::vec3 TColor::CapValues(glm::vec3 valueToCap){
	return(glm::vec3(
		CapValues(valueToCap.x),
		CapValues(valueToCap.y),
		CapValues(valueToCap.z)
	));
}

glm::vec4 TColor::CapValues(glm::vec4 valueToCap){
	return(glm::vec4(
		CapValues(valueToCap.x),
		CapValues(valueToCap.y),
		CapValues(valueToCap.z),
		CapValues(valueToCap.w)
	));
}