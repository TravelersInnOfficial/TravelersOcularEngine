#include "EventHandler.h"
#include "TOcularEngine/VideoDriver.h"

float EventHandler::zdist = 0.0f;
float EventHandler::xdist = 0.0f;


EventHandler::EventHandler(){
    m_close = false;
}

EventHandler::~EventHandler(){}

bool EventHandler::OnEvent(const TEvent& event){
    if (event.m_type == Type_Closed) m_close = true;

    if(event.m_type == Type_KeyPressed){
        if (event.m_key.code == Key_Escape){
            m_close = true;
        }
        if (event.m_key.code == Key_Left){
            //addVertices(-2, 0);
            xdist -= 0.5f;
            std::cout << "Xdist: " << xdist << "\n";
        }
        if (event.m_key.code == Key_Right){
            //addVertices(2, 0);
            xdist += 0.5f;
            std::cout << "Xdist: " << xdist << "\n";
        }
        if (event.m_key.code == Key_Down){
            //addVertices(0, -2);
            zdist -= 0.5f;
            std::cout<<"zdist: " << zdist << "\n";
        }
        if (event.m_key.code == Key_Up){
            //addVertices(0, 2);                
            zdist += 0.5f;
            std::cout<<"zdist: " << zdist << "\n";
        }
    }

    if (event.m_type == Type_KeyReleased){ 
        if(event.m_key.code == Key_Space){
        } 
    }
    return m_close;
}