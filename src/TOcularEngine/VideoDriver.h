#ifndef VIDEODRIVER_H
#define VIDEODRIVER_H

#include "./Elements/TFCamera.h"
#include "./Elements/TFLight.h"
#include "./Elements/TFMesh.h"

#include "SceneManager.h"
#include "IODriver.h"

#include <vector>

class VideoDriver{
public:
    ~VideoDriver();
    static VideoDriver* GetInstance();
    SceneManager* GetSceneManager(){return privateSceneManager;};
    IODriver* GetIOManager(){return privateIODriver;};

private:
    VideoDriver();

    SceneManager* privateSceneManager = nullptr;
    IODriver* privateIODriver = nullptr;

    std::vector<TFCamera*> m_cameras;
    std::vector<TFLight*> m_lights;
};

#endif