#include "EventHandler.h"
#include "TOcularEngine/VideoDriver.h"
#include <glm/gtc/matrix_transform.hpp>

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

        if (event.m_key.code == Key_A || event.m_key.code == Key_D || event.m_key.code == Key_S || event.m_key.code == Key_W){
        float max = 1;
        float giroY = ydistGiro;
        float giroX = xdistGiro;
        if (event.m_key.code == Key_A){ giroY -= 90.0f; giroX = 0.0f;}
        if (event.m_key.code == Key_D){ giroY += 90.0f; giroX = 0.0f;}
        if (event.m_key.code == Key_S) max = -1.0f;
        if (event.m_key.code == Key_W) max = 1.0f;

        xdist += sin(glm::radians(giroY))*cos(glm::radians(giroX))*max;
        ydist -= sin(glm::radians(giroX))*max;
        zdist += cos(glm::radians(giroY))*cos(glm::radians(giroX))*max;
        }
    }

    if(event.m_type == Type_MouseMoved){
        if(event.m_mouseMove.x>screenCenterX) ydistGiro += 1.0f;
        if(event.m_mouseMove.x<screenCenterX) ydistGiro -= 1.0f;
        if(event.m_mouseMove.y>screenCenterY) xdistGiro += 1.0f;
        if(event.m_mouseMove.y<screenCenterY) xdistGiro -= 1.0f;
    }
    
    return m_close;
}