#include "EventHandler.h"
#include "TOcularEngine/VideoDriver.h"

float EventHandler::xdist = 0.0f;
float EventHandler::ydist = 0.0f;
float EventHandler::zdist = 0.0f;
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

        if (event.m_key.code == Key_Left) xdist -= 1.0f;
        if (event.m_key.code == Key_Right) xdist += 1.0f;
        if (event.m_key.code == Key_Down) zdist -= 1.0f;
        if (event.m_key.code == Key_Up) zdist += 1.0f;

        if (event.m_key.code == Key_A) ydistGiro -= 20.0f;
        if (event.m_key.code == Key_D) ydistGiro += 20.0f;
        if (event.m_key.code == Key_S) xdistGiro -= 20.0f;
        if (event.m_key.code == Key_W) xdistGiro += 20.0f;
    }
    
    return m_close;
}