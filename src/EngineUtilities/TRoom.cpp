#include "./TRoom.h"
#include "./TPortal.h"

TRoom::TRoom(glm::vec3 size, glm::vec3 center, glm::vec3 rotation):TNode(){
	drawed = false;

	m_size = size;
	m_center = center;
	m_rotation = rotation;
}

TRoom::~TRoom(){}

void TRoom::Draw(){
	drawed = true;

	TNode::Draw();
	
	int size = m_portals.size();
	for(int i=0; i<size; i++){
		TPortal* currentPortal = m_portals[i];
		currentPortal->CheckVisibility();
	}

	drawed = false;
}

TPortal* TRoom::AddPortal(TRoom* connection, glm::vec3 size, glm::vec3 center, glm::vec3 rotation){
	TPortal* portal = new TPortal(this, connection, size, center, rotation);
	m_portals.push_back(portal);
	return portal;
}

bool TRoom::DeletePortal(TPortal* portal){
	int size = m_portals.size();
	for(int i=0; i<size; i++){
		TPortal* currentPortal = m_portals[i];
		if(currentPortal == portal){
			m_portals.erase(m_portals.begin() + i);
			return true;
		}
	}
	return false;
}

bool TRoom::GetDrawed(){
	return drawed;
}