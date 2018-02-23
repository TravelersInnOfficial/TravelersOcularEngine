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

float VideoDriver::GetTime(){
    return m_clock.getElapsedTime().asMilliseconds();
}

void VideoDriver::CreateWindow(std::string window_name, toe::core::vector2df dimensions){
    sf::ContextSettings context = sf::ContextSettings(24, 8, 4, 3);
    sf::Window m_window(sf::VideoMode(800, 600, 32), "SFML OpenGL Test", sf::Style::Close, context);
}