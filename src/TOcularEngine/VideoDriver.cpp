#include "VideoDriver.h"
#include "./../EngineUtilities/Resources/Program.h"
#include "./../EngineUtilities/TResourceManager.h"


#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h> //SIEMPRE DESPUES DE INCLUIR GLEW
std::string	VideoDriver::m_assetsPath = "";
SceneManager* VideoDriver::privateSceneManager = nullptr;
IODriver* VideoDriver::privateIODriver = nullptr;

VideoDriver::VideoDriver(){
	m_name = "";
	m_window = nullptr;
	privateSceneManager = new SceneManager();
	privateIODriver = nullptr;
	m_clearSceenColor = toe::core::TOEvector4df(0,0,0,0);
}

VideoDriver::~VideoDriver(){
	Drop();
}

void VideoDriver::Drop(){
	std::map<SHADERTYPE, Program*>::iterator it = m_programs.begin();
	for(;it!=m_programs.end();++it){
		m_programs.erase(it);
	}
	m_programs.clear();

	if(privateIODriver != nullptr)
		delete privateIODriver;
	delete privateSceneManager;
	
	glfwDestroyWindow(m_window);
	glfwTerminate();
	delete m_window;
}

void VideoDriver::glwf_error_callback(int error, const char* description){
    fprintf(stderr, "Error %d: %s\n", error, description);
}

bool VideoDriver::CreateWindows(std::string window_name, toe::core::TOEvector2df dimensions){
	m_name = window_name;

	//initialize glfw
	glfwSetErrorCallback(VideoDriver::glwf_error_callback);
    if (!glfwInit())
        return false;

	//initialize gflwindow parameters
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );

	//create glfwindow and make it the current window
	m_window = glfwCreateWindow(dimensions.X,dimensions.Y, m_name.c_str(), NULL, NULL);
    glfwMakeContextCurrent(m_window);
	SetReceiver();

	/// Iniciamos glew
	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_SMOOTH);	// Habilitar el smooth de caras
	glEnable(GL_TEXTURE_2D);	// Habilitar el test de profundidad
	glEnable(GL_DEPTH_TEST);	// Aceptar el fragmento si está más cerca de la cámara que el fragmento anterior
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);		//|
	glCullFace(GL_BACK);		//| Habilitar el backface culing

	glFrontFace(GL_CW);

	initShaders();
	privateSceneManager->InitScene();
	return true;
}

void VideoDriver::SetReceiver(){
	glfwSetKeyCallback(m_window, VideoDriver::keyboard_callback);
	glfwSetCursorPosCallback(m_window, VideoDriver::mouse_position_callback);
	glfwSetMouseButtonCallback(m_window, VideoDriver::mouse_button_callback);
	glfwSetScrollCallback(m_window, VideoDriver::mouse_scroll_callback);
}

void VideoDriver::keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(privateIODriver!=nullptr) privateIODriver->UpdateKeyboard(key,action);
}

void VideoDriver::mouse_position_callback(GLFWwindow* window, double xpos, double ypos){
	if(privateIODriver!=nullptr) privateIODriver->UpdateMousePosition(xpos,ypos);
}

void VideoDriver::mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
	if(privateIODriver!=nullptr) privateIODriver->UpdateMouseButtons(button,action);
}

void VideoDriver::mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
	if(privateIODriver!=nullptr) privateIODriver->UpdateMouseWheel(xoffset, yoffset);
}

bool VideoDriver::Update(){
	//UPDATE IO
	glfwPollEvents();
	ClearScreen();

	privateSceneManager->Update();
	return true;
}

void VideoDriver::Draw(){
	privateSceneManager->Draw();
	glUseProgram(GetProgram(STANDARD_SHADER)->GetProgramID());
	glfwSwapBuffers(m_window);
}

void VideoDriver::ClearScreen(){
	glClearColor(m_clearSceenColor.X, m_clearSceenColor.Y, m_clearSceenColor.X2, m_clearSceenColor.Y2);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

VideoDriver* VideoDriver::GetInstance(){
	static VideoDriver instance;
	return &instance;
}

SceneManager* VideoDriver::GetSceneManager(){
	return privateSceneManager;
}

IODriver* VideoDriver::GetIOManager(){
	return privateIODriver;    
}

float VideoDriver::GetTime(){
	return (float) (glfwGetTime()*1000);
}

std::string VideoDriver::GetWindowName(){
	return m_name;
}

toe::core::TOEvector2di VideoDriver::GetWindowDimensions(){
   	toe::core::TOEvector2di toRet(0.0f,0.0f);
	glfwGetWindowSize(m_window, &toRet.X, &toRet.Y);
   	return toRet;
}

Program* VideoDriver::GetProgram(SHADERTYPE p){
	return m_programs[p];
}
std::map<SHADERTYPE,Program*> VideoDriver::GetProgramVector(){
	return m_programs;
}

void VideoDriver::SetClearScreenColor(toe::core::TOEvector4df color){
	m_clearSceenColor = color;
}

void VideoDriver::SetWindowName(std::string name){
	m_name = name;
	glfwSetWindowTitle(m_window,m_name.c_str());
}

void VideoDriver::SetShaderProgram(SHADERTYPE p){
	glUseProgram(m_programs.find(p)->second->GetProgramID());
}

void VideoDriver::SetIODriver(IODriver* driver){
	privateIODriver = driver;
}

void VideoDriver::initShaders(){
	// CARGAMOS EL PROGRAMA STANDAR
		// LOAD IN RESOURCE MANAGER
		TResourceManager::GetInstance()->GetResourceShader(m_assetsPath + "/shaders/FShader.glsl");
		TResourceManager::GetInstance()->GetResourceShader(m_assetsPath + "/shaders/VShader.glsl");

		// CARGAMOS LOS SHADERS
		std::map<std::string, GLenum> shaders = std::map<std::string, GLenum>();	
		shaders.insert(std::pair<std::string, GLenum>(m_assetsPath + "/shaders/VShader.glsl", GL_VERTEX_SHADER));
		shaders.insert(std::pair<std::string, GLenum>(m_assetsPath + "/shaders/FShader.glsl", GL_FRAGMENT_SHADER));
		
		Program* p = new Program(shaders);
		m_programs.insert(std::pair<SHADERTYPE, Program*>(STANDARD_SHADER,p));

	// CARGAMOS EL PROGRAMA DE TEXTO
		// LOAD IN RESOURCE MANAGER
		TResourceManager::GetInstance()->GetResourceShader(m_assetsPath + "/shaders/VShaderText.glsl");
		TResourceManager::GetInstance()->GetResourceShader(m_assetsPath + "/shaders/FShaderText.glsl");

		// CARGAMOS LOS SHADERS
		shaders = std::map<std::string, GLenum>();
		shaders.insert(std::pair<std::string, GLenum>(m_assetsPath + "/shaders/VShaderText.glsl", GL_VERTEX_SHADER));
		shaders.insert(std::pair<std::string, GLenum>(m_assetsPath + "/shaders/FShaderText.glsl", GL_FRAGMENT_SHADER));

		p = new Program(shaders);
		m_programs.insert(std::pair<SHADERTYPE, Program*>(TEXT_SHADER, p));
	/*
	// CARGAMOS EL PROGRAMA DE 2D
		// LOAD IN RESOURCE MANAGER
		TResourceManager::GetInstance()->GetResourceShader("../src/EngineUtilities/Shaders/VShader2D.glsl");
		TResourceManager::GetInstance()->GetResourceShader("../src/EngineUtilities/Shaders/FShader2D.glsl");

		// CARGAMOS LOS SHADERS
		shaders = std::map<std::string, GLenum>();
		shaders.insert(std::pair<std::string, GLenum>("../src/EngineUtilities/Shaders/VShader2D.glsl", GL_VERTEX_SHADER));
		shaders.insert(std::pair<std::string, GLenum>("../src/EngineUtilities/Shaders/FShader2D.glsl", GL_FRAGMENT_SHADER));

		p = new Program(shaders);
		m_programs.insert(std::pair<SHADERTYPE, Program*>(TWOD_SHADER, p));
		*/
}

void VideoDriver::SetMouseVisibility(bool visible){
	if(visible == 0) glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN); //GLFW_CURSOR_DISABLED
	else glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void VideoDriver::SetCursorPosition(int x, int y){
	glfwSetCursorPos (m_window, (double) x, (double) y);
}

toe::core::TOEvector2di VideoDriver::GetCursorPosition(){
	double x, y;
	glfwGetCursorPos(m_window, &x, &y);
	return toe::core::TOEvector2di((int)x, (int)y);
}

GLFWwindow* VideoDriver::GetWindow(){
	return m_window;
}

void VideoDriver::SetAssetsPath(std::string newPath){
	 m_assetsPath = newPath;
}

std::string VideoDriver::GetAssetsPath(){
	return m_assetsPath;
}

void VideoDriver::CloseWindow(){
	if(m_window != nullptr) glfwSetWindowShouldClose(m_window, GLFW_TRUE);
}