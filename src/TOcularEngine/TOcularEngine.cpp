#include "TOcularEngine.h"

TFCamera* toe::scene::AddCamera(vector3df position, vector3df rotation, bool perspective){
    TFCamera* toRet = nullptr;
    toRet = new TFCamera(position, rotation, perspective);
    m_cameras.push_back(toRet);
    return toRet;
}

TFLight* toe::scene::AddLight(vector3df position, vector3df rotation, vector4df color, float intensity){
    TFLight* toRet = nullptr;
    toRet = new TFLight(position, rotation, color, intensity);
    m_lights.push_back(toRet);
    return toRet;
}

TFMesh* toe::scene::AddMesh(vector3df position, vector3df rotation, vector3df scale, std::string meshPath){
    TFMesh* toRet = nullptr;
    toRet = new TFMesh(position, rotation, scale, meshPath);
    return toRet;
}

float toe::core::GetTime(){
    float toRet = 0.0f;
    
    return toRet;
}