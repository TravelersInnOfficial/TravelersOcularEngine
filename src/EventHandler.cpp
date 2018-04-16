#include "EventHandler.h"
#include "TOcularEngine/VideoDriver.h"
#include <glm/gtc/matrix_transform.hpp>

int EventHandler::shaderType = 0;
float EventHandler::xdist = 0.0f;
float EventHandler::ydist = 6.0f;
float EventHandler::zdist = -10.0f;

// 0.0f,15.0f,10.0f
float EventHandler::xlight = 0.0f;
float EventHandler::ylight = 15.0f;
float EventHandler::zlight = -20.0f;

bool EventHandler::ChangeMain = false;
bool EventHandler::KP_ENTER = false;

float EventHandler::xdistGiro = 0.0f;
float EventHandler::ydistGiro = 0.0f;
float EventHandler::zdistGiro = 0.0f;
bool EventHandler::m_close = false;

EventHandler::EventHandler(){
}

EventHandler::~EventHandler(){}

static bool Keys[256];

bool EventHandler::OnEvent(const TEvent& event){
	if (event.m_type == Type_Closed) m_close = true;

	if(event.m_type == Type_KeyPressed){
		Keys[event.m_key.code] = true;

		// ONLY WHEN DOWN
		if(Keys[Key_Escape])m_close = true;
		
		if(Keys[Key_ENTER]){
			shaderType++;
			if(shaderType > 3) shaderType = 0;
		}
		
		if (Keys[Key_Space]) ChangeMain = !ChangeMain;
		if (Keys[Key_KP_ENTER]) KP_ENTER = !KP_ENTER;
	}

	if(event.m_type == Type_KeyReleased){
		Keys[event.m_key.code] = false;
	}

	if(event.m_type == Type_MouseMoved){
		if(event.m_mouseMove.x>screenCenterX) ydistGiro += 1.0f;
		if(event.m_mouseMove.x<screenCenterX) ydistGiro -= 1.0f;
		if(event.m_mouseMove.y>screenCenterY) xdistGiro += 1.0f;
		if(event.m_mouseMove.y<screenCenterY) xdistGiro -= 1.0f;
	}

	return m_close;
}

void EventHandler::Update()
{
	if(Keys[Key_A] || Keys[Key_D] || Keys[Key_S] || Keys[Key_W])
	{
		float max = 0.25f;
		float giroY = ydistGiro;
		float giroX = xdistGiro;
		
		if (Keys[Key_S]) max = -0.25f;
		if (Keys[Key_W]) max = 0.25f;
		if (Keys[Key_D]){ giroY += 90.0f; giroX = 0.0f; max = 0.25f;}
		if (Keys[Key_A]){ giroY -= 90.0f; giroX = 0.0f; max = 0.25f;}
	
		xdist += sin(glm::radians(giroY))*cos(glm::radians(giroX))*max;
		ydist -= sin(glm::radians(giroX))*max;
		zdist += cos(glm::radians(giroY))*cos(glm::radians(giroX))*max;
	}
	else
	{
		if (Keys[Key_Left])  xlight -= 0.25f;
		if (Keys[Key_Right]) xlight += 0.25f;
		if (Keys[Key_Down])  zlight -= 0.25f;
		if (Keys[Key_Up]) 	 zlight += 0.25f;
		if (Keys[Key_I]) 	 ylight += 0.25f;
		if (Keys[Key_K]) 	 ylight -= 0.25f;
	}

}