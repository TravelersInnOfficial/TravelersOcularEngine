#include "SceneManager.h"
#include "VideoDriver.h"
#include "./../EngineUtilities/Entities/TEntity.h"
#include "./../EngineUtilities/Entities/TTransform.h"
#include "./../EngineUtilities/TNode.h"

// GLEW AND GLM
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

SceneManager::SceneManager(){
	TTransform* myTransform = new TTransform();
	m_SceneTreeRoot = new TNode(myTransform);
	m_ambientLight = glm::vec3(0.25f);
	main_camera = nullptr;
}

SceneManager::~SceneManager(){
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

	glDeleteVertexArrays(1, &m_vao);
	delete m_SceneTreeRoot;
	//delete program;
}

TFCamera* SceneManager::AddCamera(toe::core::TOEvector3df position, toe::core::TOEvector3df rotation, bool perspective){
	TFCamera* toRet = nullptr;
	toRet = new TFCamera(position, rotation, perspective);
	m_cameras.push_back(toRet);
	toRet->Attach(m_SceneTreeRoot);
	main_camera = toRet;
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

TFRect* SceneManager::Add2DRect(toe::core::TOEvector2df size, toe::core::TOEvector2df position, float rotation){
	/*
	TFRect* toRet = nullptr;
	toRet = new TFRect(size,position,rotation);
	toRet->Attach(m_SceneTreeRoot);
	return toRet;
	*/
	return nullptr;
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
			if(cam == main_camera) main_camera = nullptr;
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
	TFMesh* mesh = (TFMesh*)node;

	int size = m_objects.size();
	for(int i=size-1; i>=0; i--){
		TFNode* current = m_objects[i];
		if(current == mesh){
			m_objects.erase(m_objects.begin() + i);
			delete current;
			toRet = true;
			break;
		}
	}
	/*std::vector<TFNode*>::iterator it = m_objects.begin();
	for(; it!= m_objects.end() && !toRet; ++it){
		if(*it == mesh){
			m_objects.erase(it);
			delete mesh;
			toRet = true;
		}
	}*/
	return toRet;
}

void SceneManager::Update(){
	
}

void SceneManager::SetAmbientLight(toe::core::TOEvector3df ambientLight){
	m_ambientLight = glm::vec3(ambientLight.X, ambientLight.Y, ambientLight.Z);
}

void SceneManager::Draw(){
	if(main_camera!=nullptr){
		// Select active camera and set view and projection matrix
		TEntity::SetViewMatrixPtr( main_camera->m_entityNode->GetTransformMatrix() );
		TEntity::SetViewMatrixPtr(glm::inverse(TEntity::ViewMatrix));
	}

	// Gets the Program
	Program* myProgram = VideoDriver::GetInstance()->GetProgramVector()[STANDARD_SHADER];

	// Sends the Ambient Light
	GLint ambLocation = glGetUniformLocation(myProgram->GetProgramID(), "SpecialLight.AmbientLight");
	glUniform3fv(ambLocation, 1, glm::value_ptr(m_ambientLight));

	// Send size of lights
	GLint size = m_lights.size();
	GLuint nlightspos = glGetUniformLocation(myProgram->GetProgramID(), "nlights");
	glUniform1i(nlightspos, size);

	// Draw all lights
    for(int i = 0; i < size; i++) m_lights[i]->DrawLight(i);

    m_SceneTreeRoot->Draw();
	glUseProgram(VideoDriver::GetInstance()->GetProgram(STANDARD_SHADER)->GetProgramID());
}

void SceneManager::InitScene(){
	glGenVertexArrays(1, &m_vao); // CREAMOS EL ARRAY DE VERTICES PARA LOS OBJETOS
	glBindVertexArray(m_vao);
}

TNode* SceneManager::GetRootNode(){
	return m_SceneTreeRoot;
}

TFCamera* SceneManager::GetMainCamera(){
	return main_camera;
}