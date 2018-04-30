#include "./TFPortal.h"
#include "./../../EngineUtilities/TPortal.h"

TFPortal::TFPortal(TPortal* portal, TFRoom* first, TFRoom* second){
	m_portal = portal;
	m_firstRoom = first;
	m_secondRoom = second;
}

TFPortal::~TFPortal(){
	m_portal = nullptr;
	m_firstRoom = nullptr;
	m_secondRoom = nullptr;
	// Los portales los eliminara, o bien el propio programador a través de TFRoom o al eliminar TFRoom
	// Esta clase solamente es fachada
}

void TFPortal::SetVisible(bool visible){
	m_portal->SetVisible(visible);
}

void TFPortal::SetCenter(TOEvector3df center){
	glm::vec3 input(center.X, center.Y, center.Z);
	m_portal->SetCenter(input);
}

void TFPortal::SetRotation(TOEvector3df rotation){
	glm::vec3 input(rotation.X, rotation.Y, rotation.Z);
	m_portal->SetRotation(input);
}

void TFPortal::SetSize(TOEvector3df size){
	glm::vec3 input(size.X, size.Y, size.Z);
	m_portal->SetSize(input);
}

TPortal* TFPortal::GetPortal(){
	return m_portal;
}

TFRoom* TFPortal::GetFirstRoom(){
	return m_firstRoom;
}

TFRoom* TFPortal::GetSecondRoom(){
	return m_secondRoom;
}

bool TFPortal::CheckVisibility(){
	return m_portal->CheckVisibility();
}

bool TFPortal::GetVisible(){
	return m_portal->GetVisible();
}
