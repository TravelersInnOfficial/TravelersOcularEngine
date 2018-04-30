#include "TFLight.h"
#include "./../../EngineUtilities/Entities/TTransform.h"
#include "./../../EngineUtilities/Entities/TLight.h"
#include "./../../EngineUtilities/TNode.h"
#include "./../VideoDriver.h"


// GLEW AND GLM
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

TFLight::TFLight(toe::core::TOEvector3df position, toe::core::TOEvector3df rotation, toe::core::TOEvector4df color, float attenuation) : TFNode(){
	TTransform* t = (TTransform*) m_scaleNode->GetEntity();
	t->Scale(1, 1, 1);

	t = (TTransform*) m_rotationNode->GetEntity();
	t->Rotate(rotation.X, rotation.Y, rotation.Z);

	t = (TTransform*) m_positionNode->GetEntity();
	t->Translate(position.X, position.Y, position.Z);

	glm::vec4 glmColor = glm::vec4(color.X, color.Y, color.X2, color.Y2);
	TColor myColor = TColor(glmColor);
	m_entityNode->SetEntity(new TLight(myColor, attenuation));

	m_LastLocation = glm::vec3(position.X, position.Y, position.Z);

	m_entity = TLIGHT_ENTITY;
}

TFLight::~TFLight(){
}

void TFLight::SetColor(toe::core::TOEvector4df color){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();
	glm::vec4 glmColor = glm::vec4(color.X, color.Y, color.X2, color.Y2);
	TColor myColor = TColor(glmColor);
	myEntity->SetColor(myColor);
}

void TFLight::SetAttenuation(float attenuation){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();
	myEntity->SetAttenuation(attenuation);
}

toe::core::TOEvector4df TFLight::GetColor(){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();
	glm::vec4 myColor = myEntity->GetColor().GetRGBA();
	toe::core::TOEvector4df toRetColor = toe::core::TOEvector4df(myColor.x, myColor.y, myColor.z, myColor.w);
	return toRetColor;
}

float TFLight::GetAttenuation(){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();
	return myEntity->GetAttenuation();
}

void TFLight::SetActive(bool active){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();
	myEntity->SetActive(active);
}

bool TFLight::GetActive(){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();
	return myEntity->GetActive();
}

void TFLight::SetDirectional(bool directional){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();
	myEntity->SetDirectional(directional);
}

bool TFLight::GetDirectional(){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();
	return myEntity->GetDirectional();
}

void TFLight::DrawLight(int num){
	TLight* ent = (TLight*) m_entityNode->GetEntity();

	// Initialize vectors to 0 if light is turned off
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 diffuse = glm::vec3(0.0f);
	glm::vec3 specular = glm::vec3(0.0f);
	glm::vec3 direction = glm::vec3(0.0f);
	float att = 0;
	bool directional = false;

	if(ent->GetActive()){
		toe::core::TOEvector4df color = GetColor();
		toe::core::TOEvector3df dir = GetDirection();

		position = m_LastLocation;
		diffuse = glm::vec3(color.X, color.Y, color.X2);
		specular = glm::vec3(color.X, color.Y, color.X2);
		att = GetAttenuation();
		directional = GetDirectional();

		direction = glm::vec3(dir.X, dir.Y, dir.Z);
	}

	VideoDriver* vd = VideoDriver::GetInstance();
	GLuint progID = vd->GetProgram(vd->GetCurrentProgram())->GetProgramID();

	std::string str = "Light["+std::to_string(num)+"].";
	std::string aux = "";

	aux = str +"Position";
	glUniform3fv(glGetUniformLocation(progID, aux.c_str()), 1, &position[0]);

	aux = str +"Diffuse";
	glUniform3fv(glGetUniformLocation(progID, aux.c_str()), 1, &diffuse[0]);

	aux = str +"Specular";
	glUniform3fv(glGetUniformLocation(progID, aux.c_str()), 1, &specular[0]);

	aux = str +"Attenuation";
	glUniform1f(glGetUniformLocation(progID, aux.c_str()), att);

	aux = str +"Directional";
	glUniform1i(glGetUniformLocation(progID, aux.c_str()), directional);

	aux = str +"Direction";
	glUniform3fv(glGetUniformLocation(progID, aux.c_str()), 1, &direction[0]);
}

void TFLight::DrawLightShadow(int num){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();

	if(myEntity->GetActive()){
		VideoDriver* vd = VideoDriver::GetInstance();
		GLuint progID = vd->GetProgram(SHADOW_SHADER)->GetProgramID();

		//std::string str = "Shadows["+std::to_string(num)+"].";
		//std::string aux = "";

		// Compute the MVP matrix from the light's point of view
		// SPOTLIGHT
		//glm::vec3 lightPos = m_LastLocation;
		//glm::mat4 depthProjectionMatrix = glm::perspective(glm::radians(45.0f), 1.0f, 2.0f, 50.0f);
		//glm::mat4 depthViewMatrix = glm::lookAt(lightPos, glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0,1,0));

		glm::vec3 lightInvDir = m_LastLocation;
		glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10, 10, -10, 10, 5, 40);
		glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
		glm::mat4 depthVP = depthProjectionMatrix * depthViewMatrix;

		// Send our transformation to the currently bound shader,
		// in the "MVP" uniform
		//aux = "DepthMVP";
		GLuint depthMatrixID = glGetUniformLocation(progID, "DepthMVP");
		glUniformMatrix4fv(depthMatrixID, 1, GL_FALSE, &depthVP[0][0]);

		TEntity::DepthWVP = depthVP;
	}
}

void TFLight::SetBoundBox(bool box){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();
	myEntity->drawBB = box;
}

glm::vec3 TFLight::CalculateLocation(){
	m_LastLocation = m_entityNode->GetTranslation();
	return m_LastLocation;
}

void TFLight::SetDirection(toe::core::TOEvector3df direction){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();
	myEntity->SetDirection(direction);
}

toe::core::TOEvector3df TFLight::GetDirection(){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();
	return myEntity->GetDirection();
}