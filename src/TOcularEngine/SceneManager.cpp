#include "SceneManager.h"
#include "VideoDriver.h"

SceneManager::SceneManager(){
    TTransform init_transform;
    m_SceneTreeRoot = nullptr;
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

    delete m_SceneTreeRoot;
    glDeleteVertexArrays(1, &vao);
    delete program;
}

TFCamera* SceneManager::AddCamera(toe::core::vector3df position, toe::core::vector3df rotation, bool perspective){
    TFCamera* toRet = nullptr;
    toRet = new TFCamera(position, rotation, perspective);
    m_cameras.push_back(toRet);
    toRet->Attach(m_SceneTreeRoot);
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
	glm::mat4 view = main_camera->GetTransformMatrix();
    std::map<SHADERTYPE,Program*> p = VideoDriver::GetInstance()->GetProgramVector();
    std::map<SHADERTYPE,Program*>::iterator it = p.begin();
    for(;it!=p.end();++it){
        GLint uniView = glGetUniformLocation(it->second->GetProgramID(), "ViewMatrix");
	    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
    }

    m_SceneTreeRoot->Draw();
}

// #####################################################################################################
// #####################################################################################################
// #####################################################################################################

void SceneManager::InitScene(){

    // CREAMOS EL ARRAY DE VERTICES PARA LOS OBJETOS
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // CREAMOS EL ARBOL
	TTransform* aux = new TTransform();
	TNode* parent = new TNode(aux);

	TTransform* node1Rot = new TTransform();
	TNode* node1 = new TNode(parent, node1Rot);

	aux = new TTransform();
	aux->Translate(0.0f, 0.0f, 0.0f);
	TNode* node3 = new TNode(node1, aux);

	aux = new TTransform();
	aux->Translate(0.0f, 0.0f, 0.0f);

	TMesh* mesh = new TMesh();
    TNode* miNodo = new TNode(node3, mesh);
	//mesh->SetProgram(program);

	aux = new TTransform();
	aux->Rotate(1.0f, 0.0f, 0.0f, 0.0f);
	TNode* node5 = new TNode(parent, aux);

	aux = new TTransform();
	aux->Translate(0.0f, 0.0f, -5.0f);
	TNode* node6 = new TNode(node5, aux);
	

    // CREAMOS LA CAMARA
	TCamera* camera = new TCamera(true, -1.0f, 1.0f, -0.75f, 0.75f, 2.0f, 10.0f);
	main_camera = new TNode(node6, camera);
    
    // ASIGNAMOS EL NODO ROOT
    m_SceneTreeRoot = parent;
}