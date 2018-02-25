#include "TOcularEngine.h"

VideoDriver* toe::GetVideoDriver(){
    return privateVideoDriver;
}

TFMesh* toe::AddCube(toe::core::vector3df position, toe::core::vector3df rotation, toe::core::vector3df scale){
    TFMesh* m = privateSceneManager->AddMesh(position, rotation, scale, "");
    return m;
}