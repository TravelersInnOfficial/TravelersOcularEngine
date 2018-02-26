#include "TOcularEngine.h"

VideoDriver* toe::GetVideoDriver(){
    return privateVideoDriver;
}

TFMesh* toe::AddCube(toe::core::TOEvector3df position, toe::core::TOEvector3df rotation, toe::core::TOEvector3df scale){
    TFMesh* m = privateSceneManager->AddMesh(position, rotation, scale, "");
    return m;
}