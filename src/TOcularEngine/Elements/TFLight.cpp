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

	m_LastLocation = glm::vec3(0);

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

void TFLight::DrawLight(int num){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();

	if(myEntity->GetActive()){
		VideoDriver* vd = VideoDriver::GetInstance();
		Program* myProgram = vd->GetProgram(vd->GetCurrentProgram());

		std::string str = "Light["+std::to_string(num)+"].";
		std::string aux = "";

		glm::vec3 location = m_LastLocation;
		aux = str +"Position";
		GLint lightPLocation = glGetUniformLocation(myProgram->GetProgramID(), aux.c_str());
		glUniform3fv(lightPLocation, 1, &location[0]);

		toe::core::TOEvector4df color = GetColor();
		glm::vec3 diffuse = glm::vec3(color.X, color.Y, color.X2);
		aux = str +"Diffuse";
		GLint diffLocation = glGetUniformLocation(myProgram->GetProgramID(), aux.c_str());
		glUniform3fv(diffLocation, 1, &diffuse[0]);

		glm::vec3 specular = glm::vec3(color.X, color.Y, color.X2);
		aux = str +"Specular";
		GLint specLocation = glGetUniformLocation(myProgram->GetProgramID(), aux.c_str());
		glUniform3fv(specLocation, 1, &specular[0]);

		aux = str +"Attenuation";
		GLint AttenuationLocation = glGetUniformLocation(myProgram->GetProgramID(), aux.c_str());
		float att = GetAttenuation();
		glUniform1f(AttenuationLocation, att);
	}
}

void TFLight::DrawLightShadow(int num){
	VideoDriver* vd = VideoDriver::GetInstance();
	Program* prog = vd->GetProgram(SHADOW_SHADER);

	//std::string str = "Shadows["+std::to_string(num)+"].";
	//std::string aux = "";

	// Compute the MVP matrix from the light's point of view
	// SPOTLIGHT
	//glm::vec3 lightPos = m_LastLocation;
	//glm::mat4 depthProjectionMatrix = glm::perspective(glm::radians(45.0f), 1.0f, 2.0f, 50.0f);
	//glm::mat4 depthViewMatrix = glm::lookAt(lightPos, glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0,1,0));

	glm::vec3 lightInvDir = m_LastLocation;
	glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10,10,-10,10,-10,40);
	glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
	glm::mat4 depthVP = depthProjectionMatrix * depthViewMatrix;

	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	//aux = "DepthMVP";
	GLuint depthMatrixID = glGetUniformLocation(prog->GetProgramID(), "DepthMVP");
	glUniformMatrix4fv(depthMatrixID, 1, GL_FALSE, &depthVP[0][0]);

	TEntity::DepthWVP = depthVP;
}

void TFLight::SetBoundBox(bool box){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();
	myEntity->drawBB = box;
}

glm::vec3 TFLight::CalculateLocation(){
	m_LastLocation = m_entityNode->GetTranslation();
	return m_LastLocation;
}