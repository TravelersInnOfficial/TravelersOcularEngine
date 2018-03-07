#include "EventHandler.h"
#include "TOcularEngine/VideoDriver.h"

float EventHandler::xdist = 0.0f;
float EventHandler::ydist = 0.0f;
float EventHandler::zdist = 0.0f;

EventHandler::EventHandler(){
    m_close = false;
}

EventHandler::~EventHandler(){}

float lastPosX = 0;
float lastPosY = 0;

bool EventHandler::OnEvent(const TEvent& event){
    if (event.m_type == Type_Closed) m_close = true;

    if(event.m_type == Type_KeyPressed){
        if (event.m_key.code == Key_Escape) m_close = true;
        if (event.m_key.code == Key_Left) xdist -= 4.0f;
        if (event.m_key.code == Key_Right) xdist += 4.0f;
        if (event.m_key.code == Key_Down) ydist -= 4.0f;
        if (event.m_key.code == Key_Up) ydist += 4.0f;
        if (event.m_key.code == Key_W) zdist += 4.0f;
        if (event.m_key.code == Key_S) zdist -= 4.0f;
    }

    if(event.m_type == Type_MouseMoved){
        if(event.m_mouseMove.x>lastPosX){
            lastPosX = event.m_mouseMove.x;
            ydist += 1.0f;
        }
        if(event.m_mouseMove.x<lastPosX){
            lastPosX = event.m_mouseMove.x;
            ydist -= 1.0f;
        }

        if(event.m_mouseMove.y>lastPosY){
            lastPosY = event.m_mouseMove.y;
            xdist += 1.0f;
        }
        if(event.m_mouseMove.y<lastPosY){
            lastPosY = event.m_mouseMove.y;
            xdist -= 1.0f;
        }

    }
    
    return m_close;
}