#include "IODriver.h"

IODriver::IODriver(){
    m_close = false;
}

IODriver::~IODriver(){}

bool IODriver::Update(sf::Event* event){
    if (event->type == sf::Event::Closed) m_close = true;

    if(event->type == sf::Event::KeyPressed){
        if (event->key.code == sf::Keyboard::Escape){
        m_close = true;
        }
        if (event->key.code == sf::Keyboard::Left){
            //addVertices(-2, 0);
        }
        if (event->key.code == sf::Keyboard::Right){
            //addVertices(2, 0);
        }
        if (event->key.code == sf::Keyboard::Down){
            //addVertices(0, -2);
        }
        if (event->key.code == sf::Keyboard::Up){
            //addVertices(0, 2);				
        }
    }

    if (event->type == sf::Event::KeyReleased){ 
        if(event->key.code == sf::Keyboard::Space){

        } 
    }
    return m_close;
}