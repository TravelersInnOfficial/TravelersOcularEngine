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

void SceneManager::SetAmbientLight(toe::core::TOEvector3df ambientLight){
	m_ambientLight = glm::vec3(ambientLight.X, ambientLight.Y, ambientLight.Z);
}

void SceneManager::DrawLight(TFLight* light, int num){
	Program* myProgram = VideoDriver::GetInstance()->GetProgramVector()[STANDARD_SHADER];
	std::string str = "Light["+std::to_string(num)+"].";
	std::string aux = "";

	glm::vec3 location = light->m_entityNode->GetTraslation();
	aux = str +"Position";
	GLint lightPLocation = glGetUniformLocation(myProgram->GetProgramID(), aux.c_str());
	glUniform3fv(lightPLocation, 1, glm::value_ptr(location));

	toe::core::TOEvector4df color = light->GetColor() * light->GetIntensity();
	glm::vec3 diffuse = glm::vec3(color.X, color.Y, color.X2);
	aux = str +"Diffuse";
	GLint diffLocation = glGetUniformLocation(myProgram->GetProgramID(), aux.c_str());
	glUniform3fv(diffLocation, 1, glm::value_ptr(diffuse));

	glm::vec3 specular = glm::vec3(color.X, color.Y, color.X2);
	aux = str +"Specular";
	GLint specLocation = glGetUniformLocation(myProgram->GetProgramID(), aux.c_str());
	glUniform3fv(specLocation, 1, glm::value_ptr(specular));
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
    for(int i = 0; i < size; i++){
		DrawLight(m_lights[i], i);
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