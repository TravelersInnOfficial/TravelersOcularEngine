#include "TResourceMaterial.h"

TResourceMaterial::TResourceMaterial(std::string name){
	m_name = name;
	
	// Cargamos los valores por defecto
	m_colorDifuse 		= glm::vec3(1.0f, 1.0f, 1.0f);
	m_colorSpecular 	= glm::vec3(1.0f, 1.0f, 1.0f);
	m_colorAmbient 		= glm::vec3(1.0f, 1.0f, 1.0f);
	m_colorEmmisive		= glm::vec3(1.0f, 1.0f, 1.0f);
	m_colorTransparent	= glm::vec3(1.0f, 1.0f, 1.0f);
	m_twosided = 1;
	m_shadingModel = 2;
	m_blendFunc = 2;
	m_opacity = 1.0f;
	m_shininess = 1.0f;
	m_shininessStrength = 10.0f;
	m_reflact = 1.0f;
	
	SetLoaded(false);
}

TResourceMaterial::TResourceMaterial(){
	m_name = "";
	
	// Cargamos los valores por defecto
	m_colorDifuse 		= glm::vec3(1.0f, 1.0f, 1.0f);
	m_colorSpecular 	= glm::vec3(1.0f, 1.0f, 1.0f);
	m_colorAmbient 		= glm::vec3(1.0f, 1.0f, 1.0f);
	m_colorEmmisive		= glm::vec3(1.0f, 1.0f, 1.0f);
	m_colorTransparent	= glm::vec3(1.0f, 1.0f, 1.0f);
	m_twosided = 1;
	m_shadingModel = 2;
	m_blendFunc = 2;
	m_opacity = 1.0f;
	m_shininess = 1.0f;
	m_shininessStrength = 10.0f;
	m_reflact = 1.0f;
}

TResourceMaterial::~TResourceMaterial(){

}

bool TResourceMaterial::LoadFile(){
	// En el caso del material deberia cargar en sus variables desde un principio los valores por defetcto
	bool toRet = true;
	SetLoaded(toRet);
	return toRet;
}

void TResourceMaterial::SetColorDifuse(glm::vec3 color){
	m_colorDifuse = color;
}

glm::vec3 TResourceMaterial::GetColorDifuse(){
	return m_colorDifuse;
}

void TResourceMaterial::SetColorSpecular(glm::vec3 color){
	m_colorSpecular = color;
}

glm::vec3 TResourceMaterial::GetColorSpecular(){
	return m_colorSpecular;
}

void TResourceMaterial::SetColorAmbient(glm::vec3 color){
	m_colorAmbient = color;
}

glm::vec3 TResourceMaterial::GetColorAmbient(){
	return m_colorAmbient;
}

void TResourceMaterial::SetColorEmmisive(glm::vec3 color){
	m_colorEmmisive = color;
}

glm::vec3 TResourceMaterial::GetColorEmmisive(){
	return m_colorEmmisive;
}

void TResourceMaterial::SetColorTransparent(glm::vec3 color){
	m_colorTransparent = color;
}

glm::vec3 TResourceMaterial::GetColorTransparent(){
	return m_colorTransparent;
}

void TResourceMaterial::SetTwoSided(int value){
	m_twosided = value;
}

int TResourceMaterial::GetTwoSided(){
	return m_twosided;
}

void TResourceMaterial::SetShadingMode(int value){
	m_shadingModel = value;
}

int TResourceMaterial::GetShadingMode(){
	return m_shadingModel;
}

void TResourceMaterial::SetBlendFunc(int value){
	m_blendFunc = value;
}

int TResourceMaterial::GetBlendFunc(){
	return m_blendFunc;
}

void TResourceMaterial::SetOpacity(float value){
	m_opacity = value;
}

float TResourceMaterial::GetOpacity(){
	return m_opacity;
}

void TResourceMaterial::SetShininess(float value){
	m_shininess = value;
}

float TResourceMaterial::GetShininess(){
	return m_shininess;
}

void TResourceMaterial::SetShininessStrength(float value){
	m_shininessStrength = value;
}

float TResourceMaterial::GetShininessStrength(){
	return m_shininessStrength;
}
    
void TResourceMaterial::SetReflact(float value){
	m_reflact = value;
}

float TResourceMaterial::GetReflact(){
	return m_reflact;
}
