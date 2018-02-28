#include "SceneManager.h"
#include "VideoDriver.h"
#include "../EngineUtilities/Entities/TEntity.h"

SceneManager::SceneManager(){
	m_SceneTreeRoot = new TNode(new TTransform());
	m_ambientLight = glm::vec3(0.25);
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

	size = m_meshes.size();
	for(int i = size - 1; i>=0; i--){
		delete m_meshes[i];
	}
	m_meshes.clear();

	glDeleteVertexArrays(1, &vao);
	delete m_SceneTreeRoot;
	delete program;
}

TFCamera* SceneManager::AddCamera(toe::core::TOEvector3df position, toe::core::TOEvector3df rotation, bool perspective){
	TFCamera* toRet = nullptr;
	toRet = new TFCamera(position, rotation, perspective);
	m_cameras.push_back(toRet);
	toRet->Attach(m_SceneTreeRoot);
	main_camera = toRet;
	return toRet;
}

TFLight* SceneManager::AddLight(toe::core::TOEvector3df position, toe::core::TOEvector3df rotation, toe::core::TOEvector4df color, float intensity){
	TFLight* toRet = nullptr;
	toRet = new TFLight(position, rotation, color, intensity);
	m_lights.push_back(toRet);
	toRet->Attach(m_SceneTreeRoot);
	return toRet;
}

TFMesh* SceneManager::AddMesh(toe::core::TOEvector3df position, toe::core::TOEvector3df rotation, toe::core::TOEvector3df scale, std::string meshPath){
	TFMesh* toRet = nullptr;
	toRet = new TFMesh(position, rotation, scale, meshPath);
	m_meshes.push_back(toRet);
	toRet->Attach(m_SceneTreeRoot);
	return toRet;
}

bool SceneManager::DeleteCamera(TFCamera* cam, bool deleteChildren){
	bool toRet = false;
	std::vector<TFCamera*>::iterator it = m_cameras.begin();
	for(; it != m_cameras.end() && !toRet; ++it){
		if(*it == cam){
			if(deleteChildren) std::cout<<"DELETE CHILDREN NOT IMPLEMENTED"<<std::endl;
			delete cam;
			m_cameras.erase(it);
			toRet = true;
		}
	}
	return toRet;
}

bool SceneManager::DeleteLight(TFLight* light, bool deleteChildren){
	bool toRet = false;
	std::vector<TFLight*>::iterator it = m_lights.begin();
	for(; it!= m_lights.end() && !toRet; ++it){
		if(*it == light){
			if(deleteChildren) std::cout<<"DELETE CHILDREN NOT IMPLEMENTED"<<std::endl;
			delete light;
			m_lights.erase(it);
			toRet = true;
		}
	}
	return toRet;
}

bool SceneManager::DeleteMesh(TFMesh* mesh, bool deleteChildren){
	bool toRet = false;
	std::vector<TFMesh*>::iterator it = m_meshes.begin();
	for(; it!= m_meshes.end() && !toRet; ++it){
		if(*it == mesh){
			if(deleteChildren) std::cout<<"DELETE CHILDREN NOT IMPLEMENTED"<<std::endl;
			delete mesh;
			m_meshes.erase(it);
			toRet = true;
		}
	}
	return toRet;
}

void SceneManager::Update(){
	
}

void SceneManager::SetAmbientLight(toe::core::TOEvector3df ambientLight){
	m_ambientLight = glm::vec3(ambientLight.X, ambientLight.Y, ambientLight.Z);
}

void SceneManager::Draw(){
	// Select active camera and set view and projection matrix
	TEntity::SetViewMatrixPtr( main_camera->m_entityNode->GetTransformMatrix() );

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
}

void SceneManager::InitScene(){
	glGenVertexArrays(1, &vao); // CREAMOS EL ARRAY DE VERTICES PARA LOS OBJETOS
	glBindVertexArray(vao);
}

TNode* SceneManager::GetRootNode(){
	return m_SceneTreeRoot;
}