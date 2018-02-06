#include "TLight.h"

TLight::TLight(TColor intensity){
	m_intensity = intensity;
}

TLight::~TLight(){}

void TLight::SetIntensity(TColor intensity){
	m_intensity = intensity;
}

TColor TLight::GetIntensity(){
	return m_intensity;
}

void TLight::BeginDraw(){}

void TLight::EndDraw(){}