#include "TLight.h"
#include "../TOcularEngine/VideoDriver.h"

TLight::TLight(TColor color, float intensity){
	m_color = color;
	m_intensity = intensity;
	m_program = STANDARD_SHADER;
}

TLight::~TLight(){}

void TLight::SetColor(TColor color){
	m_color = color;

}

TColor TLight::GetColor(){
	return m_color;
}

void TLight::SetIntensity(float intensity){
	m_intensity = intensity;
}

float TLight::GetIntensity(){
	return m_intensity;
}

void TLight::SetActive(bool active){
	m_active = active;
}

bool TLight::GetActive(){
	return m_active;
}

void TLight::BeginDraw(){}

void TLight::EndDraw(){}