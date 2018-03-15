#ifndef VIDEODRIVER_H
#define VIDEODRIVER_H

#include "SceneManager.h"
#include "IODriver.h"
#include <ShaderTypes.h>
#include <TOEvector2d.h>
#include <map>
#include <vector>

// Forward declaration
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

    bool CreateWindows(std::string window_name, toe::core::TOEvector2di dimensions, bool fullscreeen = false);
    bool Update();
    void BeginDraw();
	void EndDraw();
    void ClearScreen();
    void Drop();
	void CloseWindow();
    void SetReceiver();
	void SetAssetsPath(std::string newPath);
	void SetGlobalBoundingBoxes(bool enable);

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

	/**
	 * @brief Get the Screen Resolution
	 * 
	 * @return toe::core::TOEvector2di 
	 */
	toe::core::TOEvector2di GetScreenResolution();

	/**
	 * @brief Get the Window Dimensions
	 * 
	 * @return toe::core::TOEvector2di 
	 */
	toe::core::TOEvector2di GetWindowDimensions();

	/**
	 * @brief Get the Program object
	 * 
	 * @return Program* 
	 */
	Program* GetProgram(SHADERTYPE);

	/**
	 * @brief Get the Program Vector object
	 * 
	 * @return std::map<SHADERTYPE,Program*> 
	 */
	std::map<SHADERTYPE,Program*> GetProgramVector();

	/**
	 * @brief Get the Window object
	 * 
	 * @return GLFWwindow* 
	 */
	GLFWwindow* GetWindow();

	SHADERTYPE GetCurrentProgram();

	/**
	 * @brief Get the Assets Path
	 * 
	 * @return std::string 
	 */
	std::string GetAssetsPath();

	/**
	 * @brief Get the Cursor Position
	 * 
	 * @return toe::core::TOEvector2di 
	 */
	toe::core::TOEvector2di GetCursorPosition();

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

	/**
	 * @brief Set the Shader Program object
	 * 
	 * @return Program* 
	 */
	Program* SetShaderProgram(SHADERTYPE);

	/**
	 * @brief 
	 * 
	 * @param driver 
	 */
	void SetIODriver(IODriver* driver);
	
	/**
	 * @brief Set the Cursor Position object
	 * 
	 * @param x 
	 * @param y 
	 */
	void SetCursorPosition(int x, int y);

	/**
	 * @brief Set the Mouse Visibility object
	 * 
	 * @param visible 
	 */
	void SetMouseVisibility(bool visible);

private:
	/**
	 * @brief Video Driver constructor
	 * 
	 */
	VideoDriver();

	// Private GLFW window stuff
	GLFWwindow* m_window;
	std::string m_name;
	toe::core::TOEvector4df m_clearSceenColor;

	// Private Graphic Engine stuff
	static SceneManager* privateSceneManager;
	static IODriver* privateIODriver;

	// Private shaders stuff
	std::map<SHADERTYPE, Program*> m_programs;
	SHADERTYPE m_lastShaderUsed;

	/**
	 * @brief Loads the shaders in the Resource Manager
	 * 
	 */
	void initShaders();

	void start2DDrawState();
	void end2DDrawState();

	static void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_position_callback(GLFWwindow* window, double xpos, double ypos);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void window_close_callback(GLFWwindow* window);

	static void glwf_error_callback(int error, const char* description);
};

#endif