#include "TOcularEngine.h"
#include "./../EngineUtilities/TResourceManager.h"

VideoDriver* toe::GetVideoDriver(){
    privateVideoDriver = VideoDriver::GetInstance();
    privateSceneManager = VideoDriver::GetInstance()->GetSceneManager();
    privateIOManager = VideoDriver::GetInstance()->GetIOManager();
    return privateVideoDriver;
}

SceneManager* toe::GetSceneManager(){
    return privateSceneManager;
}

TFMesh* toe::AddCube(toe::core::TOEvector3df position, toe::core::TOEvector3df rotation, toe::core::TOEvector3df scale){
    TFMesh* m = privateSceneManager->AddMesh(position, rotation, scale, "");
    return m;
}

TFMesh* toe::AddSphere(toe::core::TOEvector3df position, toe::core::TOEvector3df rotation, toe::core::TOEvector3df scale){
    TFMesh* m = privateSceneManager->AddMesh(position, rotation, scale, "");
    m->CreateSphere();
    return m;
}

void toe::LoadMesh(std::string path){
	TResourceManager::GetInstance()->GetResourceMesh(path);
}

void toe::LoadTexture(std::string path){
	TResourceManager::GetInstance()->GetResourceTexture(path);
}