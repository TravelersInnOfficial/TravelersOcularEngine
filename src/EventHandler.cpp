#include "EventHandler.h"
#include "TOcularEngine/VideoDriver.h"
#include <glm/gtc/matrix_transform.hpp>

int EventHandler::shaderType = 0;
float EventHandler::xdist = 0.0f;
float EventHandler::ydist = 6.0f;
float EventHandler::zdist = -10.0f;
float EventHandler::xdistGiro = 0.0f;
float EventHandler::ydistGiro = 0.0f;
float EventHandler::zdistGiro = 0.0f;
bool EventHandler::m_close = false;

EventHandler::EventHandler(){
	Key_A_Pressed = false;
	Key_D_Pressed = false;
	Key_S_Pressed = false;
	Key_W_Pressed = false;
}

EventHandler::~EventHandler(){}

bool EventHandler::OnEvent(const TEvent& event){
	if (event.m_type == Type_Closed) m_close = true;

	if(event.m_type == Type_KeyPressed){
		if(event.m_key.code == Key_Escape) m_close = true;
		if(event.m_key.code == Key_A) Key_A_Pressed = true;
		if(event.m_key.code == Key_D) Key_D_Pressed = true;
		if(event.m_key.code == Key_S) Key_S_Pressed = true;
		if(event.m_key.code == Key_W) Key_W_Pressed = true;
		
		if(event.m_key.code == Key_ENTER){
			shaderType++;
			if(shaderType > 3) shaderType = 0;
		}
	}

	if(event.m_type == Type_KeyReleased){
		if(event.m_key.code == Key_A) Key_A_Pressed = false;
		if(event.m_key.code == Key_D) Key_D_Pressed = false;
		if(event.m_key.code == Key_S) Key_S_Pressed = false;
		if(event.m_key.code == Key_W) Key_W_Pressed = false;
	}

	if(event.m_type == Type_MouseMoved){
		if(event.m_mouseMove.x>screenCenterX) ydistGiro += 1.0f;
		if(event.m_mouseMove.x<screenCenterX) ydistGiro -= 1.0f;
		if(event.m_mouseMove.y>screenCenterY) xdistGiro += 1.0f;
		if(event.m_mouseMove.y<screenCenterY) xdistGiro -= 1.0f;
	}

	return m_close;
}

void EventHandler::Update(){

	if (Key_A_Pressed || Key_D_Pressed || Key_S_Pressed || Key_W_Pressed){
		float max = 0.25f;
		float giroY = ydistGiro;
		float giroX = xdistGiro;
		
		if (Key_S_Pressed) max = -0.25f;
		if (Key_W_Pressed) max = 0.25f;
		if (Key_D_Pressed){ giroY += 90.0f; giroX = 0.0f; max = 0.25f;}
		if (Key_A_Pressed){ giroY -= 90.0f; giroX = 0.0f; max = 0.25f;}

		xdist += sin(glm::radians(giroY))*cos(glm::radians(giroX))*max;
		ydist -= sin(glm::radians(giroX))*max;
		zdist += cos(glm::radians(giroY))*cos(glm::radians(giroX))*max;
	}

}