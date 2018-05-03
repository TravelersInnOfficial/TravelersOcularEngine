#include "TFLight.h"
#include "./../../EngineUtilities/Entities/TTransform.h"
#include "./../../EngineUtilities/Entities/TLight.h"
#include "./../../EngineUtilities/TNode.h"
#include "./../VideoDriver.h"


// GLEW AND GLM
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

TFLight::TFLight(TOEvector3df position, TOEvector3df rotation, TOEvector4df color, float attenuation) : TFNode(){
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

	m_fbo = 0;
	m_shadowMap = 0;
	
	glGenFramebuffers(1, &m_fbo);
	glGenTextures(1, &m_shadowMap);

	//#################################
	TEntity::ShadowMap = m_shadowMap;
	//#################################
	glBindTexture(GL_TEXTURE_2D, m_shadowMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_shadowMap, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (Status != GL_FRAMEBUFFER_COMPLETE) printf("FB error, status: 0x%x\n", Status);
}

TFLight::~TFLight(){
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDeleteFramebuffers(1, &m_fbo);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &m_shadowMap);
}

void TFLight::SetColor(TOEvector4df color){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();
	glm::vec4 glmColor = glm::vec4(color.X, color.Y, color.X2, color.Y2);
	TColor myColor = TColor(glmColor);
	myEntity->SetColor(myColor);
}

void TFLight::SetAttenuation(float attenuation){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();
	myEntity->SetAttenuation(attenuation);
}

TOEvector4df TFLight::GetColor(){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();
	glm::vec4 myColor = myEntity->GetColor().GetRGBA();
	TOEvector4df toRetColor = TOEvector4df(myColor.x, myColor.y, myColor.z, myColor.w);
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
		 TOEvector4df color = GetColor();
		 TOEvector3df dir = GetDirection();

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

void TFLight::CalculateShadowTexture(int num){
	if(GetActive()){
		// Change render target
		glViewport(0,0,1024,1024);						// Change viewport resolution for rendering in frame buffer 
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);	// BIND FRAME BUFFER FOR WRITING

		// Clear the screen
		glClear(GL_DEPTH_BUFFER_BIT);

		// Options
		glDisable(GL_CULL_FACE);	// DISABLE BACKFACE CULLING FOR BETER PLANNING (corners sometimes don't produce shadows)
		glEnable(GL_DEPTH_TEST);	// ENABLE ZBUFFER

		// Compute the MVP matrix from the light's point of view
		DrawLightShadow(num);

		m_SceneTreeRoot->DrawShadows();
	}
	//#################################
	else TEntity::DepthWVP = glm::mat4(0.0f);
	//#################################
}

void TFLight::DrawLightShadow(int num){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();

	if(myEntity->GetActive()){
		VideoDriver* vd = VideoDriver::GetInstance();
		GLuint progID = vd->GetProgram(SHADOW_SHADER)->GetProgramID();

		glm::vec3 lightInvDir = m_LastLocation;
		glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10, 10, -10, 10, 5, 40);
		glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
		glm::mat4 depthVP = depthProjectionMatrix * depthViewMatrix;

		// Send our transformation to the currently bound shader,
		// in the "MVP" uniform
		GLuint depthMatrixID = glGetUniformLocation(progID, "DepthMVP");
		glUniformMatrix4fv(depthMatrixID, 1, GL_FALSE, &depthVP[0][0]);

		//#################################
		TEntity::DepthWVP = depthVP;
		//#################################
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

void TFLight::SetDirection( TOEvector3df direction){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();
	myEntity->SetDirection(direction);
}

TOEvector3df TFLight::GetDirection(){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();
	return myEntity->GetDirection();
}

void TFLight::SetShadowsState(bool shadowState){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();
	myEntity->SetShadowState(shadowState);
}

bool TFLight::GetShadowsState(){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();
	return myEntity->GetShadowState();
}