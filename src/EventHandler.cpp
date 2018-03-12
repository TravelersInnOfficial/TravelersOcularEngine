#include "EventHandler.h"
#include "TOcularEngine/VideoDriver.h"

float EventHandler::xdist = 0.0f;
float EventHandler::ydist = 3.0f;
float EventHandler::zdist = -10.0f;
float EventHandler::xdistGiro = 0.0f;
float EventHandler::ydistGiro = 0.0f;
float EventHandler::zdistGiro = 0.0f;
bool EventHandler::m_close = false;

EventHandler::EventHandler(){
}

EventHandler::~EventHandler(){}

bool EventHandler::OnEvent(const TEvent& event){
    if (event.m_type == Type_Closed) m_close = true;

    if(event.m_type == Type_KeyPressed){
        if (event.m_key.code == Key_Escape) m_close = true;

        if (event.m_key.code == Key_A) xdist -= 1.0f;
        if (event.m_key.code == Key_D) xdist += 1.0f;
        if (event.m_key.code == Key_S) zdist -= 1.0f;
        if (event.m_key.code == Key_W) zdist += 1.0f;
        if (event.m_key.code == Key_Up) ydist += 1.0f;
        if (event.m_key.code == Key_Down) ydist -= 1.0f;
    }

    if(event.m_type == Type_MouseMoved){
        if(event.m_mouseMove.x>screenCenterX) ydistGiro += 1.0f;
        if(event.m_mouseMove.x<screenCenterX) ydistGiro -= 1.0f;
        if(event.m_mouseMove.y>screenCenterY) xdistGiro += 1.0f;
        if(event.m_mouseMove.y<screenCenterY) xdistGiro -= 1.0f;
    }
    
    return m_close;
}