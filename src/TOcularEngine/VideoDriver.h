#ifndef VIDEODRIVER_H
#define VIDEODRIVER_H

#define GLEW_STATIC
#include <GL/glew.h>

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

    void CreateWindow(std::string window_name, toe::core::vector2df dimensions);
    bool Update();
    void Draw();
    void ClearScreen();
    
//GETTERS
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

    /**
     * @brief Returns the actual window title
     * 
     * @return std::string m_name
     */
    std::string GetWindowName();

//SETTERS
    /**
     * @brief Sets the update clear screen color
     * 
     * @param color (toe::core::vector4df)
     */
    void SetClearScreenColor(toe::core::vector4df color);

    /**
     * @brief Sets the window title
     * 
     * @param name (std::string)
     */
    void SetWindowName(std::string name);

    void SetShaderProgram(SHADERTYPE);

    Program* GetProgram(SHADERTYPE);

    std::vector<Program*> GetProgramVector();


private:
    sf::RenderWindow* m_window;
    std::string m_name;
    sf::Clock* m_clock;

    SceneManager* privateSceneManager = nullptr;
    IODriver* privateIODriver = nullptr;

    bool close_window;
    toe::core::vector4df m_clearSceenColor;

    std::vector<Program*> m_programs;
    /**
     * @brief Video Driver constructor
     * 
     */
    VideoDriver();

    /**
     * @brief Loads the shaders in the Resource Manager
     * 
     */
    void initShaders();

};

#endif