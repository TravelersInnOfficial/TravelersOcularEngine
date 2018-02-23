#include "SceneManager.h"

SceneManager::SceneManager(){
    TTransform init_transform;
    m_SceneTreeRoot = new TNode(&init_transform);
}

SceneManager::~SceneManager(){
    for(int i = m_cameras.size(); i>=0; i--){
        delete m_cameras[i];
    }
    m_cameras.clear();
    
    for(int i = m_lights.size(); i>=0; i--){
        delete m_lights[i];
    }
    m_lights.clear();
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