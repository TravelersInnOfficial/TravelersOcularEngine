#include "SceneManager.h"
#include "VideoDriver.h"

SceneManager::SceneManager(){
	m_SceneTreeRoot = new TNode(new TTransform());
}

SceneManager::~SceneManager(){
	for(int i = m_cameras.size() - 1; i >= 0; i--){
		delete m_cameras[i];
	}
	m_cameras.clear();
	
	for(int i = m_lights.size() - 1; i >= 0; i--){
		delete m_lights[i];
	}
	m_lights.clear();

	glDeleteVertexArrays(1, &vao);
	delete m_SceneTreeRoot;
	delete program;
}

TFCamera* SceneManager::AddCamera(toe::core::vector3df position, toe::core::vector3df rotation, bool perspective){
	TFCamera* toRet = nullptr;
	toRet = new TFCamera(position, rotation, perspective);
	m_cameras.push_back(toRet);
	toRet->Attach(m_SceneTreeRoot);
	main_camera = toRet;
	return toRet;
}

TFLight* SceneManager::AddLight(toe::core::vector3df position, toe::core::vector3df rotation, toe::core::vector4df color, float intensity){
	TFLight* toRet = nullptr;
	toRet = new TFLight(position, rotation, color, intensity);
	m_lights.push_back(toRet);
	toRet->Attach(m_SceneTreeRoot);
	return toRet;
}

TFMesh* SceneManager::AddMesh(toe::core::vector3df position, toe::core::vector3df rotation, toe::core::vector3df scale, std::string meshPath){
	TFMesh* toRet = nullptr;
	toRet = new TFMesh(position, rotation, scale, meshPath);
	toRet->Attach(m_SceneTreeRoot);
	return toRet;
}

bool SceneManager::DeleteCamera(TFCamera* cam){
	bool toRet = false;
	std::vector<TFCamera*>::iterator it = m_cameras.begin();
	for(; it!= m_cameras.end(); ++it){
		if(*it == cam){ m_cameras.erase(it); toRet = true;}
	}
	return toRet;
}

bool SceneManager::DeleteLight(TFLight* light){
	bool toRet = false;
	std::vector<TFLight*>::iterator it = m_lights.begin();
	for(; it!= m_lights.end(); ++it){
		if(*it == light){ m_lights.erase(it); toRet = true;}
	}
	return toRet;
}

bool SceneManager::DeleteMesh(TFMesh* mesh){
	delete mesh;
	return true;
}

void SceneManager::Update(){
	
}

void SceneManager::Draw(){
	glm::mat4 view = main_camera->m_entityNode->GetTransformMatrix();
    std::map<SHADERTYPE,Program*> p = VideoDriver::GetInstance()->GetProgramVector();
    std::map<SHADERTYPE,Program*>::iterator it = p.begin();
    for(;it!=p.end();++it){
        GLint uniView = glGetUniformLocation(it->second->GetProgramID(), "ViewMatrix");
	    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
    }

    m_SceneTreeRoot->Draw();
}

void SceneManager::InitScene(){
	glGenVertexArrays(1, &vao); // CREAMOS EL ARRAY DE VERTICES PARA LOS OBJETOS
	glBindVertexArray(vao);
}

TNode* SceneManager::GetRootNode(){
	return m_SceneTreeRoot;
}