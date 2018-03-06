#ifndef VIDEODRIVER_H
#define VIDEODRIVER_H

#include "SceneManager.h"
#include "IODriver.h"
#include <ShaderTypes.h>
#include <TOEvector2d.h>
#include <map>
#include <vector>

// Fast-forward declaration
struct GLFWwindow;
class Program;

class VideoDriver{
    friend class TFRect;
public:
    /**
     * @brief Video Driver destructor
     * 
     */
    ~VideoDriver();

    static std::string m_assetsPath;

    bool CreateWindows(std::string window_name, toe::core::TOEvector2df dimensions);
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

    toe::core::TOEvector2di GetWindowDimensions();

    Program* GetProgram(SHADERTYPE);

    std::map<SHADERTYPE,Program*> GetProgramVector();

    void SetMouseVisibility(bool visible);

    GLFWwindow* GetWindow();

    std::string GetAssetsPath();

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

    void SetAssetsPath(std::string newPath);

private:
    /**
     * @brief Video Driver constructor
     * 
     */
    VideoDriver();

    // Private SFML stuff
    GLFWwindow* m_window;
    std::string m_name;

    // Private Graphic Engine stuff
    static SceneManager* privateSceneManager;
    static IODriver* privateIODriver;

    bool close_window;
    toe::core::TOEvector4df m_clearSceenColor;

    std::map<SHADERTYPE, Program*> m_programs;

    /**
     * @brief Loads the shaders in the Resource Manager
     * 
     */
    void initShaders();

    static void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouse_position_callback(GLFWwindow* window, double xpos, double ypos);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

    static void glwf_error_callback(int error, const char* description);
};

#endif