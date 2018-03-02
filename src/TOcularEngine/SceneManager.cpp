#include "SceneManager.h"
#include "VideoDriver.h"
#include "../EngineUtilities/Entities/TEntity.h"
#include "./Elements/TFDrawables/TFRect.h"

SceneManager::SceneManager(){
	m_SceneTreeRoot = new TNode(new TTransform());
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

TFRect* SceneManager::Add2DRect(toe::core::TOEvector2df position, toe::core::TOEvector2df size, float rotation){
	TFRect* toRet = new TFRect(size);
	toRet->SetPosition(position);
	toRet->SetOrigin(toe::core::TOEvector2df(0,0));
	toRet->SetRotation(rotation);
	toRet->SetColor(toe::core::TOEvector4df(255,0,0,255));
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

void SceneManager::DrawLight(TFLight* light){
	Program* myProgram = VideoDriver::GetInstance()->GetProgramVector()[STANDARD_SHADER];

	//glm::vec3 location = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 location = glm::vec3(light->m_positionNode->GetTraslation());
	location.z = VideoDriver::xdist;
	GLint lightPLocation = glGetUniformLocation(myProgram->GetProgramID(), "Light.Position");
	glUniform3fv(lightPLocation, 1, glm::value_ptr(location));

	//glm::vec3 ambient = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 ambient = glm::vec3(0.0f, 0.0f, 0.0f);
	GLint ambLocation = glGetUniformLocation(myProgram->GetProgramID(), "Light.Ambient");
	glUniform3fv(ambLocation, 1, glm::value_ptr(ambient));

	//glm::vec3 diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
	glm::vec3 diffuse = glm::vec3(light->GetIntensity());
	GLint diffLocation = glGetUniformLocation(myProgram->GetProgramID(), "Light.Diffuse");
	glUniform3fv(diffLocation, 1, glm::value_ptr(diffuse));

	//glm::vec3 specular = glm::vec3(1.0f, 0.0f, 0.0f);
	toe::core::TOEvector4df color = light->GetColor() * light->GetIntensity();
	
	glm::vec3 specular = glm::vec3(color.X, color.Y, color.X2);
	GLint specLocation = glGetUniformLocation(myProgram->GetProgramID(), "Light.Specular");
	glUniform3fv(specLocation, 1, glm::value_ptr(specular));
}

void SceneManager::Draw(){
	//VideoDriver::ViewMatrix = main_camera->m_entityNode->GetTransformMatrix();
	//VideoDriver::ProjMatrix = ((TCamera*)main_camera->m_entityNode->GetEntity())->GetProjectionMatrix();
	
	// Select active camera and set view and projection matrix
	TEntity::SetViewMatrixPtr( main_camera->m_entityNode->GetTransformMatrix() );
	TEntity::SetProjMatrixPtr( ( (TCamera*)(main_camera->m_entityNode->GetEntity()) )->GetProjectionMatrix() );
	
	std::vector<TFLight*>::iterator it = m_lights.begin();
    for(;it!=m_lights.end();++it){
		DrawLight(*it);
    }

	/*
	glm::mat4 view = main_camera->m_entityNode->GetTransformMatrix();
    std::map<SHADERTYPE,Program*> p = VideoDriver::GetInstance()->GetProgramVector();
    std::map<SHADERTYPE,Program*>::iterator it = p.begin();
    for(;it!=p.end();++it){
        GLint uniView = glGetUniformLocation(it->second->GetProgramID(), "ViewMatrix");
	    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
    }
*/
    m_SceneTreeRoot->Draw();
}

void SceneManager::InitScene(){
	glGenVertexArrays(1, &vao); // CREAMOS EL ARRAY DE VERTICES PARA LOS OBJETOS
	glBindVertexArray(vao);
}

TNode* SceneManager::GetRootNode(){
	return m_SceneTreeRoot;
}