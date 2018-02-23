#ifndef VIDEODRIVER_H
#define VIDEODRIVER_H

#include "SceneManager.h"
#include "IODriver.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector2d.h>

class VideoDriver{
public:
    /**
     * @brief Video Driver destructor
     * 
     */
    ~VideoDriver();

    /**
     * @brief Returns an instance of the Video Driver
     * 
     * @return VideoDriver* VideoDriver
     */
    static VideoDriver* GetInstance();

    /**
     * @brief Returns the private Scene Manager from the Video Driver
     * 
     * @return SceneManager* privateSceneManager
     */
    SceneManager* GetSceneManager(){return privateSceneManager;};

    /**
     * @brief Returns the private Input/Output Driver from the Video Driver
     * 
     * @return IODriver* privateIODriver
     */
    IODriver* GetIOManager(){return privateIODriver;};

    /**
     * @brief Returns the engine time elapsed in miliseconds
     * 
     * @return float timeElapsed
     */
    float GetTime();

    static void CreateWindow(std::string window_name, toe::core::vector2df dimensions);

private:
    /**
     * @brief Video Driver constructor
     * 
     */
    VideoDriver();

    sf::Window m_window;
    sf::Clock m_clock;

    SceneManager* privateSceneManager = nullptr;
    IODriver* privateIODriver = nullptr;
};

#endif