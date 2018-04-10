#include "./TFRoom.h"
#include "./../../EngineUtilities/TRoom.h"

TFRoom::TFRoom(toe::core::TOEvector3df position, toe::core::TOEvector3df rotation, toe::core::TOEvector3df scale) : TFNode(){
	glm::vec3 size(scale.X, scale.Y, scale.Z);
	glm::vec3 center(position.X, position.Y, position.Z);
	glm::vec3 rot(rotation.X, rotation.Y, rotation.Z);

	TRoom* newRoom = new TRoom(size, center, rot);

	if(m_entityNode!=nullptr) delete m_entityNode;

	m_entityNode = newRoom;
	newRoom->SetParent(m_positionNode);
	m_positionNode->AddChild(newRoom);

	m_entity = TROOM_ENTITY;
}

TFRoom::~TFRoom(){
	int size = m_portals.size();
	for(int i=0; i<size; i++){
		delete m_portals[i];
	}
	m_portals.clear();
}

TFPortal* TFRoom::AddConnection(TFRoom* room, toe::core::TOEvector3df position, toe::core::TOEvector3df rotation, toe::core::TOEvector3df scale){
	// Que hago con el TPortal que devuelve el AddPortal?
	ENTITYTYPE type = room->m_entity;
	if(type == TROOM_ENTITY){
		TRoom* connectionRoom = (TRoom*)room->GetEntityNode();
		TRoom* currentRoom = (TRoom*)m_entityNode;

		TPortal* portal = currentRoom->AddPortal(connectionRoom,  glm::vec3(scale.X, scale.Y, scale.Z),
												glm::vec3(position.X, position.Y, position.Z),
												glm::vec3(rotation.X, rotation.Y, rotation.Z));

		TFPortal* fPortal = new TFPortal(portal);
		m_portals.push_back(fPortal);

		return fPortal;
	}
	return nullptr;
}

bool TFRoom::DeletePortal(TFPortal* portal){
	TRoom* room =(TRoom*)m_entityNode;
	bool output = room->DeletePortal(portal->GetPortal());
	delete portal;
	return output;
}

void TFRoom::SetTranslate(toe::core::TOEvector3df translation){
	TRoom* currentRoom = (TRoom*)m_entityNode;
	currentRoom->SetCenter(glm::vec3(translation.X, translation.Y, translation.Z));
}

void TFRoom::SetRotation(toe::core::TOEvector3df rotation){
	TRoom* currentRoom = (TRoom*)m_entityNode;
	currentRoom->SetRotation(glm::vec3(rotation.X, rotation.Y, rotation.Z));
}

void TFRoom::SetScale(toe::core::TOEvector3df scale){
	TRoom* currentRoom = (TRoom*)m_entityNode;
	currentRoom->SetSize(glm::vec3(scale.X, scale.Y, scale.Z));
}	

void TFRoom::Translate(toe::core::TOEvector3df translation){
	TRoom* currentRoom = (TRoom*)m_entityNode;
	currentRoom->Translate(glm::vec3(translation.X, translation.Y, translation.Z));
}

void TFRoom::Rotate(toe::core::TOEvector3df rotation){
	TRoom* currentRoom = (TRoom*)m_entityNode;
	currentRoom->Rotate(glm::vec3(rotation.X, rotation.Y, rotation.Z));
}

void TFRoom::Scale(toe::core::TOEvector3df scale){
	TRoom* currentRoom = (TRoom*)m_entityNode;
	currentRoom->Scale(glm::vec3(scale.X, scale.Y, scale.Z));
}

toe::core::TOEvector3df TFRoom::GetTranslation(){
	TRoom* currentRoom = (TRoom*)m_entityNode;
	glm::vec3 center = currentRoom->GetCenter();
	return toe::core::TOEvector3df(center.x, center.y, center.z);
}

toe::core::TOEvector3df TFRoom::GetRotation(){
	TRoom* currentRoom = (TRoom*)m_entityNode;
	glm::vec3 rot = currentRoom->GetRotation();
	return toe::core::TOEvector3df(rot.x, rot.y, rot.z);
}

toe::core::TOEvector3df TFRoom::GetScale(){
	TRoom* currentRoom = (TRoom*)m_entityNode;
	glm::vec3 scale = currentRoom->GetSize();
	return toe::core::TOEvector3df(scale.x, scale.y, scale.z);
}

float TFRoom::GetDistance(toe::core::TOEvector3df position){
	TRoom* currentRoom = (TRoom*)m_entityNode;
	return currentRoom->GetDistance(glm::vec3(position.X, position.Y, position.Z));
}

TNode* TFRoom::GetConnectionNode(){
	return m_entityNode;
}
