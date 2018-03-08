#include "TLight.h"
#include "../TOcularEngine/VideoDriver.h"

TLight::TLight(TColor color, float attenuation){
	m_color = color;
	m_attenuation = attenuation;
	m_program = STANDARD_SHADER;
}

TLight::~TLight(){}

void TLight::SetColor(TColor color){
	m_color = color;

}

TColor TLight::GetColor(){
	return m_color;
}

void TLight::SetAttenuation(float attenuation){
	m_attenuation = attenuation;
}

float TLight::GetAttenuation(){
	return m_attenuation;
}

void TLight::SetActive(bool active){
	m_active = active;
}

bool TLight::GetActive(){
	return m_active;
}

void TLight::BeginDraw(){}

void TLight::EndDraw(){}