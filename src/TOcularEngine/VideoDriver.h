#ifndef VIDEODRIVER_H
#define VIDEODRIVER_H

#define GLEW_STATIC
#include <GL/glew.h>

#include "SceneManager.h"
#include "IODriver.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <TOEvector2d.h>

class VideoDriver{
public:
    /**
     * @brief Video Driver destructor
     * 
     */
    ~VideoDriver();

    void CreateWindows(std::string window_name, toe::core::TOEvector2df dimensions);
    bool Update();
    void Draw();
    void ClearScreen();
    void Drop();

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
    SceneManager* GetSceneManager();

    /**
     * @brief Returns the private Input/Output Driver from the Video Driver
     * 
     * @return IODriver* privateIODriver
     */
    IODriver* GetIOManager();

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

    toe::core::TOEvector2df GetWindowDimensions();

    Program* GetProgram(SHADERTYPE);

    std::map<SHADERTYPE,Program*> GetProgramVector();

    void SetMouseVisibility(bool visible);

//SETTERS
    /**
     * @brief Sets the update clear screen color
     * 
     * @param color (toe::core::TOEvector4df)
     */
    void SetClearScreenColor(toe::core::TOEvector4df color);

    /**
     * @brief Sets the window title
     * 
     * @param name (std::string)
     */
    void SetWindowName(std::string name);

    void SetShaderProgram(SHADERTYPE);

    void SetIODriver(IODriver* driver);

    void SetCursorPosition(int x, int y);

    toe::core::TOEvector2di GetCursorPosition();

private:
    /**
     * @brief Video Driver constructor
     * 
     */
    VideoDriver();

    // Private SFML stuff
    sf::RenderWindow* m_window;
    std::string m_name;
    sf::Clock* m_clock;

    // Private Graphic Engine stuff
    SceneManager* privateSceneManager = nullptr;
    IODriver* privateIODriver = nullptr;

    bool close_window;
    toe::core::TOEvector4df m_clearSceenColor;

    std::map<SHADERTYPE, Program*> m_programs;

    /**
     * @brief Loads the shaders in the Resource Manager
     * 
     */
    void initShaders();

};

#endif