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

TFMesh* toe::AddCube(TOEvector3df position, TOEvector3df rotation, TOEvector3df scale){
    TFMesh* m = privateSceneManager->AddMesh(position, rotation, scale, "");
    return m;
}

TFMesh* toe::AddSphere(TOEvector3df position, TOEvector3df rotation, TOEvector3df scale){
    TFMesh* m = privateSceneManager->AddMesh(position, rotation, scale, "");
    m->CreateSphere();
    return m;
}

TFRect* toe::Add2DRect(TOEvector2df position, TOEvector2df size, float rotation){
    TFRect* toRet = privateSceneManager->Add2DRect(position, size, rotation);
    return toRet;
}

TF2DText* toe::Add2DText(std::string text, TOEvector2df position){
    TF2DText* toRet = privateSceneManager->Add2DText(text, position);
    return toRet;
}


TFSprite* toe::AddSprite(std::string texture, TOEvector2df position, TOEvector2df size){
    TFSprite* toRet = privateSceneManager->AddSprite(texture, position, size);
    return toRet;
}

void toe::LoadMesh(std::string path){
	TResourceManager::GetInstance()->GetResourceMesh(path);
}

void toe::LoadTexture(std::string path){
	TResourceManager::GetInstance()->GetResourceTexture(path);
}

GLuint toe::GetTextureID(std::string path){
    return TResourceManager::GetInstance()->GetResourceTexture(path)->GetTextureId();
}

TOEvector2di toe::GetTextureDims(std::string path){
    int w = TResourceManager::GetInstance()->GetResourceTexture(path)->GetWidth();
    int h = TResourceManager::GetInstance()->GetResourceTexture(path)->GetHeight();
    return TOEvector2di(w,h);
}

int toe::GetTextureWidth(std::string path){
    return TResourceManager::GetInstance()->GetResourceTexture(path)->GetWidth();
}

int toe::GetTextureHeight(std::string path){
    return TResourceManager::GetInstance()->GetResourceTexture(path)->GetHeight();
}