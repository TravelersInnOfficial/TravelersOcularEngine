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
	m_depthWVP = glm::mat4(0.0f);
}

TFLight::~TFLight(){
	if(GetShadowsState()) EraseShadow();
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
	bool shadowlight = false;

	if(ent->GetActive()){
		TOEvector4df color = GetColor();
		TOEvector3df dir = GetDirection();
		position = m_LastLocation;
		diffuse = glm::vec3(color.X, color.Y, color.X2);
		specular = glm::vec3(color.X, color.Y, color.X2);
		att = GetAttenuation();
		directional = GetDirectional();
		direction = glm::vec3(dir.X, dir.Y, dir.Z);
		shadowlight = GetShadowsState();
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

	if(directional){
		aux = str +"Direction";
		glUniform3fv(glGetUniformLocation(progID, aux.c_str()), 1, &direction[0]);
	}

	aux = str +"ShadowLight";
	glUniform1i(glGetUniformLocation(progID, aux.c_str()), shadowlight);

	if(shadowlight){
		// SEND THE SHADOW MAP
		aux = str +"ShadowMap";
		GLint textureNumber = 50 + num;	// Empezamos en el 50 para dejar sitio a las demas texturas
		glActiveTexture(GL_TEXTURE0 + textureNumber);
		glBindTexture(GL_TEXTURE_2D, m_shadowMap);
		glUniform1i(glGetUniformLocation(progID, aux.c_str()), textureNumber);
	}
}
// SEND MVP TO THE SHADER
void TFLight::DrawLightMVP(int num){
	// CALCULATE
	glm::mat4 biasMatrix(
			0.5, 0.0, 0.0, 0.0,
			0.0, 0.5, 0.0, 0.0,
			0.0, 0.0, 0.5, 0.0,
			0.5, 0.5, 0.5, 1.0
	);
	glm::mat4 depthBIASMVP = biasMatrix * m_depthWVP;

	// SEND
	std::string aux = "DepthBiasMVPArray["+std::to_string(num)+"]";
	VideoDriver* vd = VideoDriver::GetInstance();
	GLuint progID = vd->GetProgram(vd->GetCurrentProgram())->GetProgramID();
	glUniformMatrix4fv(glGetUniformLocation(progID, aux.c_str()), 1, GL_FALSE, &depthBIASMVP[0][0]);
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

// SHADOWS #####################################################################################################################
//##############################################################################################################################

void TFLight::SetShadowsState(bool shadowState){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();
	
	// Si de verdad se esta cambiando	
	if(GetShadowsState() != shadowState){
		// Iniciamos o borramos la informacion de las sombras
		if(!shadowState) EraseShadow();
		else InitShadow();
		myEntity->SetShadowsState(shadowState);
	}
}

bool TFLight::GetShadowsState(){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();
	return myEntity->GetShadowsState();
}

void TFLight::InitShadow(){

	std::cout<<"Generamos el FBO y bindeamos el shadow map"<<std::endl;

	m_fbo = 0;
	m_shadowMap = 0;

	glGenFramebuffers(1, &m_fbo); 

	glGenTextures(1, &m_shadowMap);
	glBindTexture(GL_TEXTURE_2D, m_shadowMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_shadowMap, 0);

	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (Status != GL_FRAMEBUFFER_COMPLETE) printf("FB error, status: 0x%x\n", Status);
}

void TFLight::EraseShadow(){

	std::cout<<"Borramos los datos de las sombras"<<std::endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDeleteFramebuffers(1, &m_fbo);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &m_shadowMap);
	m_depthWVP = glm::mat4(0.0f);
	m_fbo = 0;
	m_shadowMap = 0;
}

bool TFLight::CalculateShadowTexture(int num){
	bool paintBuffer = false;

	if(GetActive() && GetShadowsState()){

		std::cout<<"Bindeamos el frame buffer para pintar la textura de sombras de la luz numero "<<num<<std::endl;

		paintBuffer = true;
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
	}

	return paintBuffer;
}

// DEBERIA SER DIFERENTE PARA LUCES DE PUNTO
void TFLight::DrawLightShadow(int num){

	std::cout<<"Calculamos la DepthMVP de la luz numero "<<num<<" y se la pasamos a TENTITY (de donde la cogera el shader de sombras para pintar la textura de sombras)"<<std::endl;

	// Fill variables
	glm::vec3 lightInvDir = m_LastLocation;

	// Get the orthogonal view of the light
	glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10, 10, -10, 10, -10, 100);
	
	// Calculate the direction of the light
	//TOEvector3df dir = GetDirection();
	//glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(dir.X,dir.Y,dir.Z), glm::vec3(0.0f,1.0f,0.0f));
	
	// ARREGLAR PARA QUE APUNTE AL MISMO LUGAR QUE LA LUZ, NO AL CENTRO SIEMPRE
	glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0,0,0), glm::vec3(0.0f,1.0f,0.0f));
	glm::mat4 depthModelMatrix = glm::mat4(1.0);
	glm::mat4 depthVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;

	m_depthWVP = depthVP;
	TEntity::DepthWVP = m_depthWVP;	//Only for the shadow texture calculation

	// Enviar al shader actual
	//VideoDriver* vd = VideoDriver::GetInstance();
	//GLuint progID = vd->GetProgram(SHADOW_SHADER)->GetProgramID();
	//GLuint depthMatrixID = glGetUniformLocation(progID, "DepthMVP");
	//glUniformMatrix4fv(depthMatrixID, 1, GL_FALSE, &depthVP[0][0]);
}

// SHADOWS #####################################################################################################################
//##############################################################################################################################