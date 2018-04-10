#include "./TFPortal.h"
#include "./../../EngineUtilities/TPortal.h"

TFPortal::TFPortal(TPortal* portal){
	m_portal = portal;
}

TFPortal::~TFPortal(){
	// Los portales los eliminara, o bien el propio programador a través de TFRoom o al eliminar TFRoom
	// Esta clase solamente es fachada
}

void TFPortal::SetVisible(bool visible){
	m_portal->SetVisible(visible);
}

void TFPortal::SetCenter(toe::core::TOEvector3df center){
	glm::vec3 input(center.X, center.Y, center.Z);
	m_portal->SetCenter(input);
}

void TFPortal::SetRotation(toe::core::TOEvector3df rotation){
	glm::vec3 input(rotation.X, rotation.Y, rotation.Z);
	m_portal->SetRotation(input);
}

void TFPortal::SetSize(toe::core::TOEvector3df size){
	glm::vec3 input(size.X, size.Y, size.Z);
	m_portal->SetSize(input);
}

TPortal* TFPortal::GetPortal(){
	return m_portal;
}

