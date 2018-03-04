#include "VideoDriver.h"
#include "./../EngineUtilities/Resources/Program.h"
#include "./../EngineUtilities/TResourceManager.h"


#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h> //SIEMPRE DESPUES DE INCLUIR GLEW
std::string	VideoDriver::m_assetsPath = "";

VideoDriver::VideoDriver(){
	m_name = "";
	m_window = nullptr;
	m_clock = new sf::Clock;
	privateSceneManager = new SceneManager();
	privateIODriver = nullptr;
	close_window = false;
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
	delete m_clock;
	delete m_window;
}

void VideoDriver::CreateWindows(std::string window_name, toe::core::TOEvector2df dimensions){
	m_name = window_name;

	m_window = glfwCreateWindow(dimensions.X,dimensions.Y, m_name.c_str(), NULL, NULL);
    glfwMakeContextCurrent(m_window);
	
	/// Iniciamos glew
	glewExperimental = GL_TRUE;
	glewInit();

	glShadeModel(GL_SMOOTH);	// Habilitar el smooth de caras
	glEnable(GL_TEXTURE_2D);	// Habilitar el test de profundidad
	glEnable(GL_DEPTH_TEST);	// Aceptar el fragmento si está más cerca de la cámara que el fragmento anterior
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);		//|
	glCullFace(GL_BACK);		//| Habilitar el backface culing

	initShaders();
	privateSceneManager->InitScene();
}

bool VideoDriver::Update(){
	//UPDATE IO
	/*
	sf::Event event;
	while (m_window->pollEvent(event)){
		if(privateIODriver != nullptr)
			close_window = privateIODriver->Update(&event);
			m_events.push_back(&event);
	}

	ClearScreen();

	if(close_window) m_window->close();
	if(!close_window) privateSceneManager->Update();
	*/
	return !close_window;
}

void VideoDriver::Draw(){
	//privateSceneManager->Draw();

	// Volvemos a poner el shader por default para el display de los datos
	glUseProgram(GetProgram(STANDARD_SHADER)->GetProgramID());
	//m_window->display(); 
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
	return m_clock->getElapsedTime().asMilliseconds();
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
	//m_window->setMouseCursorVisible(visible);
	if(visible == 0) glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN); //GLFW_CURSOR_DISABLED
	else glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void VideoDriver::SetCursorPosition(int x, int y){
	//sf::Mouse::setPosition(sf::Vector2i(x, y), *m_window);
}

toe::core::TOEvector2di VideoDriver::GetCursorPosition(){
	//sf::Vector2i auxVec = sf::Mouse::getPosition(*m_window);
	return toe::core::TOEvector2di(0, 0);
}

std::vector<sf::Event*> VideoDriver::GetSFMLEvents(){
	std::vector<sf::Event*> toRet = m_events;
	m_events.clear();
	return toRet;
}

GLFWwindow* VideoDriver::GetWindow(){
	return m_window;
}

sf::Time VideoDriver::GetElapsedTime(){
	return m_clock->getElapsedTime();
}

void VideoDriver::SetAssetsPath(std::string newPath){
	 m_assetsPath = newPath;
}

std::string VideoDriver::GetAssetsPath(){
	return m_assetsPath;
}