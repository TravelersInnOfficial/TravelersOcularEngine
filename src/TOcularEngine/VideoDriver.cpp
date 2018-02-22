#include "VideoDriver.h"

VideoDriver::VideoDriver(){
    privateSceneManager = new SceneManager();
    privateIODriver = new IODriver();
}

VideoDriver* VideoDriver::GetInstance(){
    static VideoDriver instance;
    return &instance;
}

VideoDriver::~VideoDriver(){
    delete privateSceneManager;
    delete privateIODriver;
}
