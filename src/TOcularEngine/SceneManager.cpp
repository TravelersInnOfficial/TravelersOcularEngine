#include "SceneManager.h"
#include "VideoDriver.h"
#include "./../EngineUtilities/Entities/TEntity.h"
#include "./../EngineUtilities/Entities/TTransform.h"
#include "./../EngineUtilities/TNode.h"

#include <algorithm>    // std::find

// GLEW AND GLM
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

SceneManager::SceneManager(){
	TTransform* myTransform = new TTransform();
	m_SceneTreeRoot = new TNode(myTransform);
	m_ambientLight = glm::vec3(0.25f);
	m_main_camera = nullptr;
	m_dome = nullptr;

	m_vao = 0;
	m_fbo = 0;
	m_shadowMap = 0;
}

SceneManager::~SceneManager(){
	ClearElements();
	glDeleteVertexArrays(1, &m_vao);

	glDeleteFramebuffers(1, &m_fbo);
	glDeleteTextures(1, &m_shadowMap);
}

TFCamera* SceneManager::AddCamera(toe::core::TOEvector3df position, toe::core::TOEvector3df rotation, bool perspective){
	TFCamera* toRet = nullptr;
	toRet = new TFCamera(position, rotation, perspective);
	m_cameras.push_back(toRet);
	toRet->Attach(m_SceneTreeRoot);
	m_main_camera = toRet;
	return toRet;
}

TFLight* SceneManager::AddLight(toe::core::TOEvector3df position, toe::core::TOEvector3df rotation, toe::core::TOEvector4df color, float attenuation){
	TFLight* toRet = nullptr;
	toRet = new TFLight(position, rotation, color, attenuation);
	m_lights.push_back(toRet);
	toRet->Attach(m_SceneTreeRoot);
	return toRet;
}

TFMesh* SceneManager::AddMesh(toe::core::TOEvector3df position, toe::core::TOEvector3df rotation, toe::core::TOEvector3df scale, std::string meshPath){
	TFMesh* toRet = nullptr;
	toRet = new TFMesh(position, rotation, scale, meshPath);
	m_objects.push_back((TFMesh*)toRet);
	toRet->Attach(m_SceneTreeRoot);
	return toRet;
}

TFDome* SceneManager::AddDome(toe::core::TOEvector3df position, std::string texturePath){
	if(m_dome == nullptr){
		TFDome* toRet = new TFDome(position, toe::core::TOEvector3df(0.0f,0.0f,0.0f), toe::core::TOEvector3df(50.0f,50.0f,50.0f), texturePath);
		m_dome = toRet;
		m_dome->AttachFirst(m_SceneTreeRoot);	
	}
	else if(texturePath.compare("") != 0) m_dome->SetTexture(texturePath);
	return m_dome;
}

TFRect* SceneManager::Add2DRect(toe::core::TOEvector2df position, toe::core::TOEvector2df size, float rotation){
	TFRect* toRet = new TFRect(position, size, rotation);
	m_bkg2Delems.push_back(toRet);
	return toRet;
}

TFSprite* SceneManager::AddSprite(std::string texture, toe::core::TOEvector2df position, toe::core::TOEvector2df size){
	TFSprite* toRet =  new TFSprite(texture, position, size);
	m_bkg2Delems.push_back(toRet);
	return toRet;
}

void SceneManager::PushToBkg(TFDrawable* obj){
	std::vector<TFDrawable*>::iterator it = m_2Delems.begin();
	for(; it!=m_2Delems.end(); ++it){
		if(*it == obj){
			m_bkg2Delems.push_back(*it);
			m_2Delems.erase(it);
			break;
		}
	}
}

void SceneManager::PushToFront(TFDrawable* obj){
	std::vector<TFDrawable*>::iterator it = m_bkg2Delems.begin();
	for(; it!=m_bkg2Delems.end(); ++it){
		if(*it == obj){
			m_2Delems.push_back(*it);
			m_bkg2Delems.erase(it);
			break;
		}
	}
}

void SceneManager::Delete2Delement(TFDrawable* elem){
	bool find = false;
	std::vector<TFDrawable*>::iterator it = m_2Delems.begin();

	for(; it != m_2Delems.end(); ++it){
		if(*it == elem){ 
			m_2Delems.erase(it);
			find = true;
			break;
		}
	}
	if(!find){
		it = m_bkg2Delems.begin();
		for(; it != m_bkg2Delems.end(); ++it){
			if(*it == elem){ 
				m_bkg2Delems.erase(it);
				break;
			}
		}
	}
}

TFParticleSystem* SceneManager::AddParticleSystem(toe::core::TOEvector3df position, toe::core::TOEvector3df rotation, toe::core::TOEvector3df scale){
	TFParticleSystem* toRet = nullptr;
	toRet = new TFParticleSystem(position, rotation, scale);
	m_objects.push_back(toRet);
	toRet->Attach(m_SceneTreeRoot);
	return toRet;
}

bool SceneManager::DeleteCamera(TFCamera* cam){
	bool toRet = false;
	std::vector<TFCamera*>::iterator it = m_cameras.begin();
	for(; it != m_cameras.end() && !toRet; ++it){
		if(*it == cam){
			if(cam == m_main_camera) m_main_camera = nullptr;
			delete cam;
			m_cameras.erase(it);
			toRet = true;
		}
	}
	return toRet;
}

bool SceneManager::DeleteLight(TFLight* light){
	bool toRet = false;
	std::vector<TFLight*>::iterator it = m_lights.begin();
	for(; it!= m_lights.end() && !toRet; ++it){
		if(*it == light){
			delete light;
			m_lights.erase(it);
			toRet = true;
		}
	}
	return toRet;
}

bool SceneManager::DeleteMesh(TFNode* node){
	bool toRet = false;

	std::vector<TFNode*>::iterator it = m_objects.begin();
	for(; it!= m_objects.end() && !toRet; ++it){
		if(*it == node){
			m_objects.erase(it);
			delete node;
			toRet = true;
		}
	}
	return toRet;
}

void SceneManager::SetAmbientLight(toe::core::TOEvector3df ambientLight){
	m_ambientLight = glm::vec3(ambientLight.X, ambientLight.Y, ambientLight.Z);
}

toe::core::TOEvector3df SceneManager::GetAmbientLight(){
	return toe::core::TOEvector3df(m_ambientLight.x, m_ambientLight.y, m_ambientLight.z);
}

void SceneManager::SetMainCameraData(){
	if(m_main_camera!=nullptr){
		TEntity::SetViewMatrixPtr( glm::inverse(m_main_camera->m_entityNode->GetTransformMatrix()) );
	}
}

TNode* SceneManager::GetRootNode(){
	return m_SceneTreeRoot;
}

TFCamera* SceneManager::GetMainCamera(){
	return m_main_camera;
}

void SceneManager::ChangeMainCamera(TFCamera* camera){
	// En el caso de que se pase un nullptr vamos a querer poner la siguiente camara
	// es por eso que vamos tanto a buscar si esta la camera pasada como la main camera
	int cameraPos = -1;
	int mainCameraPos = -1;
	int size = m_cameras.size();
	for(int i=0; i<size; i++){
		TFCamera* current = m_cameras[i];
		// Buscamos la main Camera
		if(current == m_main_camera){
			mainCameraPos = i;
			// En el caso de que no haya camara pasada podemos salir del bucle
			if(camera == nullptr) break;
		}
		// Buscamos la Camara pasada, si es nullptr nunca se encontrara
		if(current == camera){
			cameraPos = -1;
			break;	// Como ya hemos encontrado la camara podemos salir
		}
	}

	// En el caso de que no se haya encontrado la camara o era nullptr
	if(cameraPos == -1){
		cameraPos = mainCameraPos + 1;
		// En el caso de que nos pasemos volvemos al principio
		if(cameraPos == size) cameraPos = 0;
	}
	m_main_camera = m_cameras[cameraPos];
}

void SceneManager::InitScene(){
	glGenVertexArrays(1, &m_vao); // CREAMOS EL ARRAY DE VERTICES PARA LOS OBJETOS
	glBindVertexArray(m_vao);

	glGenFramebuffers(1, &m_fbo); 

	glGenTextures(1, &m_shadowMap);
	TEntity::ShadowMap = m_shadowMap;
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

	if (Status != GL_FRAMEBUFFER_COMPLETE) {
		printf("FB error, status: 0x%x\n", Status);
		//return false;
	} 
}

void SceneManager::Update(){
	// MOVE DOME WITH CAMERA
	if(m_main_camera != nullptr && m_dome != nullptr){
		toe::core::TOEvector3df position = m_main_camera->GetTranslation();
		m_dome->SetTranslate(position);
	}
}

void SceneManager::Draw(){
	// Draw into frame for shadows
	DrawSceneShadows();

	// Draw frame into window
	int width = VideoDriver::GetInstance()->GetWindowDimensions().X;
	int height = VideoDriver::GetInstance()->GetWindowDimensions().Y;

	// Draw into window
	glViewport(0,0,width,height);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// IMPORTANT CLEAR COLOR
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// ENABLE BACK FACE CULLING
	glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK); // Cull back-facing triangles -> draw only front-facing triangles

	// Select active camera and set view and projection matrix
	SetMainCameraData();

	// Send lights position to shader
	SendLights();

    m_SceneTreeRoot->Draw();
}

void SceneManager::DrawBkg2DElements(){
	//DRAW 2D ELEMENTS AFTER THE 3D SCENE
	for(int i = 0; i<m_bkg2Delems.size(); i++) m_bkg2Delems[i]->Draw();
}

void SceneManager::Draw2DElements(){
	//DRAW 2D ELEMENTS AT THE END OF DRAWING
	for(int i = 0; i< m_2Delems.size(); i++) m_2Delems[i]->Draw();
}

void SceneManager::DrawBoundingBoxes(bool draw){
	int size = m_objects.size();
	for(int i = size - 1; i>=0 ; i--){
		m_objects[i]->SetBoundBox(draw);
	}
}

void SceneManager::ChangeShader(SHADERTYPE shader, ENTITYTYPE entity){
	int size = m_objects.size();
	for(int i=0; i<size; i++){
		TFNode* currentNode = m_objects[i];
		currentNode->SetProgram(shader, entity);
	}
}

void SceneManager::RecalculateLightPosition(){
	GLint size = m_lights.size();
	for(int i = 0; i < size; i++) m_lights[i]->CalculateLocation();
}

void SceneManager::SendLights(){
	// Change light last position
	RecalculateLightPosition();
	
	// Gets the Program
	VideoDriver* vd = VideoDriver::GetInstance();
	Program* myProgram = vd->SetShaderProgram(STANDARD_SHADER);

	// Sends the Ambient Light
	GLint ambLocation = glGetUniformLocation(myProgram->GetProgramID(), "SpecialLight.AmbientLight");
	glUniform3fv(ambLocation, 1, &m_ambientLight[0]);

	// Send size of lights
	GLint size = m_lights.size();
	GLuint nlightspos = glGetUniformLocation(myProgram->GetProgramID(), "nlights");
	glUniform1i(nlightspos, size);

	// Draw all lights
    for(int i = 0; i < size; i++) m_lights[i]->DrawLight(i);

}

void SceneManager::DrawSceneShadows()
{
	// Set shadow program
	VideoDriver::GetInstance()->SetShaderProgram(SHADOW_SHADER);
	RecalculateLightPosition();

	int size = m_dynamicLights.size();
	for(int i = 0; i < size; i++){
		
		// BIND FRAME BUFFER FOR WRITING
		glViewport(0,0,1024,1024); // Render on the whole framebuffer, complete from the lower left corner to the upper right
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);

		// Clear the screen
		glClear(GL_DEPTH_BUFFER_BIT);

		// DISABLE BACKFACE CULLING FOR PETER PLANNING
		glDisable(GL_CULL_FACE);

		// ENABLE ZBUFFER
		glEnable(GL_DEPTH_TEST);
	
		// Compute the MVP matrix from the light's point of view
		m_dynamicLights[i]->DrawLightShadow(i);
	} 

	m_SceneTreeRoot->DrawShadows();
}

bool SceneManager::AddDynamicLight(TFLight* light){
	bool ret = true;
	// Find light then add at the back
	if ( std::find(m_dynamicLights.begin(), m_dynamicLights.end(), light) != m_dynamicLights.end() ){
		ret = false;
	}
	else{
		m_dynamicLights.push_back(light);		
	}

	return ret;
}

void SceneManager::ResetManager(){
	ClearElements();
	TTransform* myTransform = new TTransform();
	m_SceneTreeRoot = new TNode(myTransform);
	//m_ambientLight = glm::vec3(0.25f);
	m_main_camera = nullptr;
	m_dome = nullptr;
}

void SceneManager::SetClipping(bool value){
	TEntity::m_checkClipping = value;
}

// PRIVATE FUNCTIONS
void SceneManager::ClearElements(){
	int size = m_cameras.size();
	for(int i = size - 1; i >= 0; i--){
		delete m_cameras[i];
	}
	m_cameras.clear();
	
	size = m_lights.size();
	for(int i = size - 1; i >= 0; i--){
		delete m_lights[i];
	}
	m_lights.clear();

	size = m_objects.size();
	for(int i = size - 1; i>=0; i--){
		delete m_objects[i];
	}
	m_objects.clear();

	size = m_bkg2Delems.size();
	for (int i = size -1; i>=0; i--) delete m_bkg2Delems[i];
	m_bkg2Delems.clear();

	size = m_2Delems.size();
	for(int i = size - 1; i>=0; i--) delete m_2Delems[i];
	m_2Delems.clear();

	delete m_SceneTreeRoot;
	m_SceneTreeRoot = nullptr;
	m_dome = nullptr;
}
