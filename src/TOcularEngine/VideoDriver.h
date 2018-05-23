#ifndef VIDEODRIVER_H
#define VIDEODRIVER_H

/**
 * @brief Manages Window creation and Rendering Programs.
 * 
 * @file VideoDriver.h
 */

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
	 */
	~VideoDriver();

	static std::string m_assetsPath;	// m_assetsPath - Ruta hasta los assets del motor

	/**
	 * @brief	- Creamos una nueva ventana 
	 * 
	 * @param 	- window_name - Nombre de la ventana
	 * @param 	- dimensions - Tamanyo de la ventana
	 * @param 	- fullscreeen - Si queremos la ventana en pantalla completa
	 * @return 	- bool - Si la ventana se ha creado correctamente
	 */
    bool CreateWindows(std::string window_name, TOEvector2di dimensions, bool fullscreeen = false);
    
    /**
     * @brief	- Update del VideoDriver 
     * 				Actualizamos la pila de eventos, limpiamos la pantalla y hacemos update del SceneManager
     */
    bool Update();

    /**
     * @brief	- Empezamos a pintar los elementos del sceneManager
     * 				empezando por los 3D y continuando por los elementos del fondo  
     */
    void BeginDraw();

    /**
     * @brief 	- Acabamos de pintar, pintando los elementos 2D
     */
	void EndDraw();

	/**
	 * @brief	- Limpiamos la pantalla pintandola del color predeterminado
	 */
    void ClearScreen();

    /**
     * @brief	- Limpiamos todos los datos del VideoDriver 
     */
    void Drop();

    /**
     * @brief 	- Enviamos una senyal para decir que se debe cerrar la ventana
     */
	void CloseWindow();

	/**
	 * @brief	- Actualizamos los metodos que reciben datos de glfw 
	 */
    void SetReceiver();

    /**
     * @brief	- Cambia la ruta de los assets del motor 
     */
	void SetAssetsPath(std::string newPath);

	/**
	 * @brief	- Cambia la variable para pintar todos los bounding boxes 
	 */
	void SetGlobalBoundingBoxes(bool enable);
	
	/**
	 * @brief	- Minimiza la ventana 
	 */
	void Minimize();

	/**
	 * @brief	- Activa el clipping 
	 */
	void EnableClipping();

	/**
	 * @brief	- Desactiva el clipping 
	 */
	void DisableClipping();

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
	 * @return TOEvector2di 
	 */
	TOEvector2di GetScreenResolution();

	/**
	 * @brief Get the Window Resolution
	 * @return TOEvector2di 
	 */
	TOEvector2di GetWindowResolution();

	/**
	 * @brief Get the Window Dimensions
	 * 
	 * @return TOEvector2di 
	 */
	TOEvector2di GetWindowDimensions();

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
	std::map<SHADERTYPE,Program*>& GetProgramVector();

	/**
	 * @brief Get the Window object
	 * 
	 * @return GLFWwindow* 
	 */
	GLFWwindow* GetWindow();

	/**
	 * @brief	- Devuelve el ultimo shader que ha utilizado el VideoDriver 
	 */
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
	 * @return TOEvector2di 
	 */
	TOEvector2di GetCursorPosition();

//SETTERS
	/**
	 * @brief Sets the update clear screen color
	 * 
	 * @param color (TOEvector4df)
	 */
	void SetClearScreenColor(TOEvector4df color);

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

	/**
	 * @brief	- Cambia el shader que estan utilizando las entidades 
	 * 
	 * @param 	- shader - Shader al que cambiar
	 * @param 	- entity - Tipo de entidad al que cambiarle el shader
	 */
	void ChangeShader(SHADERTYPE shader, ENTITYTYPE entity);

private:
	/**
	 * @brief Video Driver constructor
	 */
	VideoDriver();

	// Private GLFW window stuff
	GLFWwindow* m_window;				// m_window - Ventana de glfw
	std::string m_name;					// m_name - Nombre de la ventana
	TOEvector4df m_clearSceenColor;		// m_clearSceenColor - Color con el que limpiar la ventana

	// Private Graphic Engine stuff
	static SceneManager* privateSceneManager;	// priavetSceneManager - Puntero al SceneManager
	static IODriver* privateIODriver;			// privateIODriver - Puntero al IODriver

	// Private shaders stuff
	std::map<SHADERTYPE, Program*> m_programs;	// m_programs - Programas cargados en el driver
	SHADERTYPE m_lastShaderUsed;				// m_lastShaderUsed - Ultimo shader utilizado

	/**
	 * @brief Loads the shaders in the Resource Manager
	 * 
	 */
	void initShaders();

	/**
	 * @brief	- Cambia las variables de Opengl para empezar a pintar en 2D
	 */
	void start2DDrawState();

	/**
	 * @brief	- Vuelve a poner las variables de Opengl a como estaban para pintar en 3D 
	 */
	void end2DDrawState();

	/**
	 * @brief	- Metodos a los que llama glfw para resolvar su lista de eventos
	 */
	static void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_position_callback(GLFWwindow* window, double xpos, double ypos);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void window_close_callback(GLFWwindow* window);
	static void glwf_error_callback(int error, const char* description);
};

#endif