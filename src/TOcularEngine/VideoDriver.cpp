#include "VideoDriver.h"

VideoDriver::VideoDriver(){
    m_name = "";
    m_window = nullptr;
    m_clock = new sf::Clock;
    privateSceneManager = new SceneManager();
    privateIODriver = new IODriver();
    close_window = false;
    m_clearSceenColor = toe::core::TOEvector4df(0,0,0,0);
}

VideoDriver* VideoDriver::GetInstance(){
    static VideoDriver instance;
    return &instance;
}

VideoDriver::~VideoDriver(){
    std::map<SHADERTYPE, Program*>::iterator it = m_programs.begin();
    for(;it!=m_programs.end();++it){
        m_programs.erase(it);
    }
    m_programs.clear();

    delete privateIODriver;
    delete privateSceneManager;
    delete m_clock;
    delete m_window;
}

float VideoDriver::GetTime(){
    return m_clock->getElapsedTime().asMilliseconds();
}

void VideoDriver::CreateWindow(std::string window_name, toe::core::TOEvector2df dimensions){
    m_name = window_name;

    sf::ContextSettings context = sf::ContextSettings(24, 8, 4, 3);
    m_window = new sf::RenderWindow(sf::VideoMode(dimensions.X, dimensions.Y), m_name.c_str(), sf::Style::Titlebar | sf::Style::Close, context);
    
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
    sf::Event event;
    while (m_window->pollEvent(event)){
        close_window = privateIODriver->Update(&event);
    }

    ClearScreen();

    if(close_window) m_window->close();
    if(!close_window) privateSceneManager->Update();
    return !close_window;
}

void VideoDriver::Draw(){
    privateSceneManager->Draw();
    m_window->display();
}

void VideoDriver::ClearScreen(){
    glClearColor(m_clearSceenColor.X, m_clearSceenColor.Y, m_clearSceenColor.X2, m_clearSceenColor.Y2);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void VideoDriver::SetClearScreenColor(toe::core::TOEvector4df color){
    m_clearSceenColor = color;
}

void VideoDriver::SetWindowName(std::string name){
    m_name = name;
    m_window->setTitle(m_name.c_str());
}

std::string VideoDriver::GetWindowName(){
    return m_name;
}

void VideoDriver::SetShaderProgram(SHADERTYPE p){
	glUseProgram(m_programs.find(p)->second->GetProgramID());
}

void VideoDriver::initShaders(){
    //LOAD IN RESOURCE MANAGER
    TResourceManager::GetInstance()->GetResourceShader("../src/EngineUtilities/Shaders/VShader.glsl");
    TResourceManager::GetInstance()->GetResourceShader("../src/EngineUtilities/Shaders/FShader.glsl");

    //CARGAMOS LOS SHADERS
	std::map<std::string, GLenum> shaders = std::map<std::string, GLenum>();	
	shaders.insert(std::pair<std::string, GLenum>("../src/EngineUtilities/Shaders/VShader.glsl", GL_VERTEX_SHADER));
	shaders.insert(std::pair<std::string, GLenum>("../src/EngineUtilities/Shaders/FShader.glsl", GL_FRAGMENT_SHADER));
    
    Program* p = new Program(shaders);
    glUseProgram(p->GetProgramID());
    m_programs.insert(std::pair<SHADERTYPE, Program*>(STANDARD_SHADER,p));
}

Program* VideoDriver::GetProgram(SHADERTYPE p){
    return m_programs[p];
}
std::map<SHADERTYPE,Program*> VideoDriver::GetProgramVector(){
    return m_programs;
}