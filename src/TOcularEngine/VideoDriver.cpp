#include "VideoDriver.h"

VideoDriver::VideoDriver(){
    m_name = "";
    m_window = nullptr;
    m_clock = new sf::Clock;
    privateSceneManager = new SceneManager();
    privateIODriver = new IODriver();
    close_window = false;
    m_clearSceenColor = toe::core::vector4df(0,0,0,0);
}

VideoDriver* VideoDriver::GetInstance(){
    static VideoDriver instance;
    return &instance;
}

VideoDriver::~VideoDriver(){
    delete privateIODriver;
    delete privateSceneManager;
    delete m_clock;
    delete m_window;
}

float VideoDriver::GetTime(){
    return m_clock->getElapsedTime().asMilliseconds();
}

void VideoDriver::CreateWindow(std::string window_name, toe::core::vector2df dimensions){
    m_name = window_name;
    m_window = new sf::RenderWindow(sf::VideoMode(dimensions.X, dimensions.Y), m_name.c_str(), sf::Style::Titlebar | sf::Style::Close);
    
    /// Iniciamos glew
	glewExperimental = GL_TRUE;
	glewInit();

	glShadeModel(GL_SMOOTH);	// Habilitar el smooth de caras
	glEnable(GL_TEXTURE_2D);	// Habilitar el test de profundidad
	glEnable(GL_DEPTH_TEST);	// Aceptar el fragmento si está más cerca de la cámara que el fragmento anterior
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);		//|
	glCullFace(GL_BACK);		//| Habilitar el backface culing

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

void VideoDriver::SetClearScreenColor(toe::core::vector4df color){
    m_clearSceenColor = color;
}

void VideoDriver::SetWindowName(std::string name){
    m_name = name;
    m_window->setTitle(m_name.c_str());
}

std::string VideoDriver::GetWindowName(){
    return m_name;
}