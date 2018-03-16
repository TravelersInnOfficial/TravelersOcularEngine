#include "VideoDriver.h"
#include "./../EngineUtilities/Resources/Program.h"
#include "./../EngineUtilities/TResourceManager.h"
#include <stdio.h>
#include <string.h>

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h> //SIEMPRE DESPUES DE INCLUIR GLEW
std::string	VideoDriver::m_assetsPath = "";
SceneManager* VideoDriver::privateSceneManager = nullptr;
IODriver* VideoDriver::privateIODriver = nullptr;

VideoDriver::VideoDriver(){
	// Init variables
	m_name = "";
	m_lastShaderUsed = NONE_SHADER;
	m_window = nullptr;
	m_clearSceenColor = toe::core::TOEvector4df(0,0,0,0);

	// Init engine stuff
	privateSceneManager = new SceneManager();
	privateIODriver = nullptr;
	
	// Iinitialize GLFW
	glfwSetErrorCallback(VideoDriver::glwf_error_callback);
    glfwInit();
}

VideoDriver::~VideoDriver(){
	Drop();
}

// Main functions
bool VideoDriver::CreateWindows(std::string window_name, toe::core::TOEvector2di dimensions, bool fullscreen){
	m_name = window_name;

	//initialize gflwindow parameters
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
	glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST); 

	//create glfwindow and make it the current window
	GLFWmonitor* monitor = nullptr;
	if(fullscreen){
		glfwWindowHint( GLFW_DECORATED, GL_FALSE );
		monitor = glfwGetPrimaryMonitor();
	}
	m_window = glfwCreateWindow(dimensions.X,dimensions.Y, m_name.c_str(), monitor, NULL);
    
	glfwMakeContextCurrent(m_window);
	SetReceiver();

	/// Iniciamos glew
	glewExperimental = GL_TRUE;
	glewInit();

	glShadeModel(GL_SMOOTH);		//|
	glEnable(GL_POLYGON_SMOOTH);	//| Habilitar el smooth de caras
	glEnable(GL_TEXTURE_2D);		// Habilitar el test de profundidad
	glEnable(GL_DEPTH_TEST);		// Aceptar el fragmento si está más cerca de la cámara que el fragmento anterior
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);			//|
	glCullFace(GL_BACK);			//| Habilitar el backface culing
	glFrontFace(GL_CW);

	glShadeModel(GL_SMOOTH); 

	initShaders();
	privateSceneManager->InitScene();
	return true;
}

bool VideoDriver::Update(){
	//UPDATE IO
	glfwPollEvents();
	ClearScreen();

	privateSceneManager->Update();
	return true;
}

void VideoDriver::Draw(){
	//DRAW 3D SCENE
	privateSceneManager->Draw();

	//DRAW 2D ELEMENTS
	start2DDrawState();
	privateSceneManager->Draw2DElements();
	end2DDrawState();

	SetShaderProgram(STANDARD_SHADER);
	glfwSwapBuffers(m_window);
}

void VideoDriver::ClearScreen(){
	glClearColor(m_clearSceenColor.X, m_clearSceenColor.Y, m_clearSceenColor.X2, m_clearSceenColor.Y2);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void VideoDriver::Drop(){
	std::map<SHADERTYPE, Program*>::iterator it = m_programs.begin();
	for(;it!=m_programs.end();++it) delete it->second;
	m_programs.clear();

	if(privateIODriver != nullptr) delete privateIODriver;
	if(privateSceneManager != nullptr) delete privateSceneManager;

	glfwDestroyWindow(m_window);
	glfwTerminate();
	//delete m_window; // Ya la elimina GLFW con el DestroyWindow
}

void VideoDriver::CloseWindow(){
	if(m_window != nullptr) glfwSetWindowShouldClose(m_window, GLFW_TRUE);
}

void VideoDriver::SetReceiver(){
	glfwSetKeyCallback(m_window, VideoDriver::keyboard_callback);
	glfwSetCursorPosCallback(m_window, VideoDriver::mouse_position_callback);
	glfwSetMouseButtonCallback(m_window, VideoDriver::mouse_button_callback);
	glfwSetScrollCallback(m_window, VideoDriver::mouse_scroll_callback);
	glfwSetWindowCloseCallback(m_window, VideoDriver::window_close_callback);
}

void VideoDriver::SetAssetsPath(std::string newPath){
	 m_assetsPath = newPath;
}

void VideoDriver::SetGlobalBoundingBoxes(bool enable){
	// Iterate all meshes
	privateSceneManager->DrawBoundingBoxes(enable);
}

// Getters
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

toe::core::TOEvector2di VideoDriver::GetCursorPosition(){
	double x, y;
	glfwGetCursorPos(m_window, &x, &y);
	return toe::core::TOEvector2di((int)x, (int)y);
}

GLFWwindow* VideoDriver::GetWindow(){
	return m_window;
}

std::string VideoDriver::GetAssetsPath(){
	return m_assetsPath;
}

toe::core::TOEvector2di VideoDriver::GetScreenResolution(){
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    return toe::core::TOEvector2di(mode->width, mode->height);
}

toe::core::TOEvector2di VideoDriver::GetWindowResolution(){
	int x = 0;
	int y = 0;
	if(m_window != nullptr) glfwGetWindowSize(m_window, &x, &y); 	
	return toe::core::TOEvector2di(x, y);
}

// Setters
void VideoDriver::SetClearScreenColor(toe::core::TOEvector4df color){
	m_clearSceenColor = color;
}

void VideoDriver::SetWindowName(std::string name){
	m_name = name;
	glfwSetWindowTitle(m_window,m_name.c_str());
}

Program* VideoDriver::SetShaderProgram(SHADERTYPE p){
	Program* toRet = m_programs.find(p)->second;
	if(m_lastShaderUsed != p){
		glUseProgram(toRet->GetProgramID());
	}
	m_lastShaderUsed = p;

	return toRet;
}

void VideoDriver::SetIODriver(IODriver* driver){
	privateIODriver = driver;
}

void VideoDriver::SetMouseVisibility(bool visible){
	//if(visible == 0) glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	//else glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	if(visible == 0){
		int w = 1;
		int h = 1;
		unsigned char pixels[w * h * 4];
		memset(pixels, 0x00, sizeof(pixels));
		GLFWimage image;
		image.width = w;
		image.height = h;
		image.pixels = pixels;
		GLFWcursor* newCursor = glfwCreateCursor(&image, 0, 0);
		glfwSetCursor(m_window, newCursor);
	}

	else{
		GLFWcursor* newCursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
		glfwSetCursor(m_window, newCursor);
	}
}

void VideoDriver::SetCursorPosition(int x, int y){
	glfwSetCursorPos (m_window, (double) x, (double) y);
}

// Private Functions
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

	// CARGAMOS EL PROGRAMA DE PARTICULAS
		// LOAD IN RESOURCE MANAGER
		TResourceManager::GetInstance()->GetResourceShader(m_assetsPath + "/shaders/VShaderParticle.glsl");
		TResourceManager::GetInstance()->GetResourceShader(m_assetsPath + "/shaders/FShaderParticle.glsl");

		// CARGAMOS LOS SHADERS
		shaders = std::map<std::string, GLenum>();
		shaders.insert(std::pair<std::string, GLenum>(m_assetsPath + "/shaders/VShaderParticle.glsl", GL_VERTEX_SHADER));
		shaders.insert(std::pair<std::string, GLenum>(m_assetsPath + "/shaders/FShaderParticle.glsl", GL_FRAGMENT_SHADER));

		p = new Program(shaders);
		m_programs.insert(std::pair<SHADERTYPE, Program*>(PARTICLE_SHADER, p));
	
	// CARGAMOS EL PROGRAMA DE POLIGONOS 2D 
		// LOAD IN RESOURCE MANAGER
		TResourceManager::GetInstance()->GetResourceShader(m_assetsPath + "/shaders/VShader2D.glsl");
		TResourceManager::GetInstance()->GetResourceShader(m_assetsPath + "/shaders/FShader2D.glsl");

		// CARGAMOS LOS SHADERS
		shaders = std::map<std::string, GLenum>();
		shaders.insert(std::pair<std::string, GLenum>(m_assetsPath + "/shaders/VShader2D.glsl", GL_VERTEX_SHADER));
		shaders.insert(std::pair<std::string, GLenum>(m_assetsPath + "/shaders/FShader2D.glsl", GL_FRAGMENT_SHADER));

		p = new Program(shaders);
		m_programs.insert(std::pair<SHADERTYPE, Program*>(TWOD_SHADER, p));

	// CARGAMOS EL PROGRAMA DE SPRITES
		// LOAD IN RESOURCE MANAGER
		TResourceManager::GetInstance()->GetResourceShader(m_assetsPath + "/shaders/VShaderSprites.glsl");
		TResourceManager::GetInstance()->GetResourceShader(m_assetsPath + "/shaders/FShaderSprites.glsl");

		// CARGAMOS LOS SHADERS
		shaders = std::map<std::string, GLenum>();
		shaders.insert(std::pair<std::string, GLenum>(m_assetsPath + "/shaders/VShaderSprites.glsl", GL_VERTEX_SHADER));
		shaders.insert(std::pair<std::string, GLenum>(m_assetsPath + "/shaders/FShaderSprites.glsl", GL_FRAGMENT_SHADER));

		p = new Program(shaders);
		m_programs.insert(std::pair<SHADERTYPE, Program*>(SPRITE_SHADER, p));	

	// CARGAMOS EL PROGRAMA DE BOUNDIN BOXES
		// LOAD IN RESOURCE MANAGER
		TResourceManager::GetInstance()->GetResourceShader(m_assetsPath + "/shaders/VShaderBB.glsl");
		TResourceManager::GetInstance()->GetResourceShader(m_assetsPath + "/shaders/FShaderBB.glsl");

		// CARGAMOS LOS SHADERS
		shaders = std::map<std::string, GLenum>();
		shaders.insert(std::pair<std::string, GLenum>(m_assetsPath + "/shaders/VShaderBB.glsl", GL_VERTEX_SHADER));
		shaders.insert(std::pair<std::string, GLenum>(m_assetsPath + "/shaders/FShaderBB.glsl", GL_FRAGMENT_SHADER));

		p = new Program(shaders);
		m_programs.insert(std::pair<SHADERTYPE, Program*>(BB_SHADER, p));	
}

void VideoDriver::start2DDrawState(){

	//GUARDAMOS EL ESTADO ACTUAL
	glMatrixMode(GL_PROJECTION);	//activamos la matriz Projection
	glPushMatrix(); 				//guardamos en la pila el estado actual de la matriz Projection
	glLoadIdentity(); 				//cargamos la matriz identidad en la matriz Projection

	//creamos una vista ortografica de la camara
	toe::core::TOEvector2di dims = GetWindowDimensions();	//cojemos las dimensiones de la ventana
	glOrtho(0, dims.X, dims.Y, 0, -1.0f, 1.0f);				//sup-izq, inf-izq, inf-der, sup-der, near, far

	glMatrixMode(GL_MODELVIEW);		//activamos la matriz ModelView
	glPushMatrix(); 				//guardamos en la pila el estado actual de la matriz ModelView
	glLoadIdentity(); 				//cargamos la matriz identidad en la matriz ModelView
	
	glPushAttrib(GL_DEPTH_TEST);	//guardamos en la pila el estado actual del test de profundidad
	glDepthMask(GL_FALSE);			//desactivamos la escritura en el buffer de profundidad
	glDisable(GL_DEPTH_TEST);		//desactivamos el test de profundidad
	glDisable(GL_CULL_FACE);		//desactivamos el backface culling

	///////////////////////////////////
	///////////START 2D DRAW///////////
	///////////////////////////////////
}

void VideoDriver::end2DDrawState(){
	///////////////////////////////////
	////////////END 2D DRAW////////////
	///////////////////////////////////
	//VOLVER AL ESTADO ANTERIOR
	glPopAttrib();					//recuperamos de la pila el estado del test de profundidad
	glDepthMask(GL_TRUE); 			//activamos la escritura en el buffer de profundidad
	glEnable(GL_DEPTH_TEST);		//activamos el test de profundidad
	glEnable(GL_CULL_FACE);			//activamos el backface culling

	glMatrixMode(GL_MODELVIEW);		//activamos la matriz ModelView
	glPopMatrix();					//recuperamos el estado anterior de la pila y se lo asignamos
	glMatrixMode(GL_PROJECTION);	//activamos la matriz Projection
	glPopMatrix();					//recuperamos el estado anterior de la pila y se lo asignamos
}

void VideoDriver::keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(privateIODriver!=nullptr) privateIODriver->UpdateKeyboard(key,action);
}

void VideoDriver::mouse_position_callback(GLFWwindow* window, double xpos, double ypos){
	if(privateIODriver!=nullptr) privateIODriver->UpdateMousePosition(xpos,ypos);
}
void VideoDriver::window_close_callback(GLFWwindow* window){
	if(privateIODriver!=nullptr) privateIODriver->UpdateShouldClose();
}

void VideoDriver::mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
	if(privateIODriver!=nullptr) privateIODriver->UpdateMouseButtons(button,action);
}

void VideoDriver::mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
	if(privateIODriver!=nullptr) privateIODriver->UpdateMouseWheel(xoffset, yoffset);
}

void VideoDriver::glwf_error_callback(int error, const char* description){
    fprintf(stderr, "Error %d: %s\n", error, description);
}
