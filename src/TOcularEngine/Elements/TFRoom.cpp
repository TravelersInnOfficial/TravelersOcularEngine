#include "./TFRoom.h"
#include "./../../EngineUtilities/TRoom.h"
#include "./../VideoDriver.h"

TFRoom::TFRoom(TOEvector3df position, TOEvector3df rotation, TOEvector3df scale) : TFNode(){
	glm::vec3 size(scale.X, scale.Y, scale.Z);
	glm::vec3 center(position.X, position.Y, position.Z);
	glm::vec3 rot(rotation.X, rotation.Y, rotation.Z);

	TRoom* newRoom = new TRoom(size, center, rot);

	if(m_entityNode!=nullptr) delete m_entityNode;

	m_entityNode = newRoom;
	newRoom->SetParent(m_positionNode);
	m_positionNode->AddChild(newRoom);

	m_entity = TROOM_ENTITY;

	lightsSend = false;
}

TFRoom::~TFRoom(){
	int size = m_portals.size();
	for(int i=0; i<size; i++){
		delete m_portals[i];
	}
	m_portals.clear();

	m_roomLights.clear();
}

TFPortal* TFRoom::AddConnection(TFRoom* room, TOEvector3df position, TOEvector3df rotation, TOEvector3df scale){
	// Que hago con el TPortal que devuelve el AddPortal?
	ENTITYTYPE type = room->m_entity;
	if(type == TROOM_ENTITY){
		TRoom* connectionRoom = (TRoom*)room->GetEntityNode();
		TRoom* currentRoom = (TRoom*)m_entityNode;

		TPortal* portal = currentRoom->AddPortal(connectionRoom,  glm::vec3(scale.X, scale.Y, scale.Z),
												glm::vec3(position.X, position.Y, position.Z),
												glm::vec3(rotation.X, rotation.Y, rotation.Z));

		TFPortal* fPortal = new TFPortal(portal, this, room);
		m_portals.push_back(fPortal);

		return fPortal;
	}
	return nullptr;
}

int TFRoom::DrawLights(int value, int nextTo){
	int output = value;

	if(!lightsSend){
		lightsSend = true;

		int size = m_roomLights.size();
		for(int i=0;i<size && value+i<=12; i++){
			m_roomLights[i]->DrawLight(value + i);
			output++;
		}

		if(output<=12){	
			size = m_portals.size();
			for(int i=0; i<size; i++){
				if(m_portals[i]->GetVisible() && (nextTo > 0 || m_portals[i]->CheckVisibility())){
					output = m_portals[i]->GetSecondRoom()->DrawLights(output, nextTo-1);
				}
			}
		}
	}

	return output;
}

void TFRoom::SetLightsSend(bool value){
	lightsSend = value;
}

void TFRoom::Draw(){
	TRoom* room = (TRoom*)m_entityNode;
	room->Draw();
}

void TFRoom::SetDrawed(bool value){
	TRoom* room = (TRoom*)m_entityNode;
	room->SetDrawed(value);
}

bool TFRoom::DeletePortal(TFPortal* portal){
	TRoom* room =(TRoom*)m_entityNode;
	bool output = room->DeletePortal(portal->GetPortal());
	delete portal;
	return output;
}

void TFRoom::SetTranslate(TOEvector3df translation){
	TRoom* currentRoom = (TRoom*)m_entityNode;
	currentRoom->SetCenter(glm::vec3(translation.X, translation.Y, translation.Z));
}

void TFRoom::SetRotation(TOEvector3df rotation){
	TRoom* currentRoom = (TRoom*)m_entityNode;
	currentRoom->SetRotation(glm::vec3(rotation.X, rotation.Y, rotation.Z));
}

void TFRoom::SetScale(TOEvector3df scale){
	TRoom* currentRoom = (TRoom*)m_entityNode;
	currentRoom->SetSize(glm::vec3(scale.X, scale.Y, scale.Z));
}	

void TFRoom::Translate(TOEvector3df translation){
	TRoom* currentRoom = (TRoom*)m_entityNode;
	currentRoom->Translate(glm::vec3(translation.X, translation.Y, translation.Z));
}

void TFRoom::Rotate(TOEvector3df rotation){
	TRoom* currentRoom = (TRoom*)m_entityNode;
	currentRoom->Rotate(glm::vec3(rotation.X, rotation.Y, rotation.Z));
}

void TFRoom::Scale(TOEvector3df scale){
	TRoom* currentRoom = (TRoom*)m_entityNode;
	currentRoom->Scale(glm::vec3(scale.X, scale.Y, scale.Z));
}

TOEvector3df TFRoom::GetTranslation(){
	TRoom* currentRoom = (TRoom*)m_entityNode;
	glm::vec3 center = currentRoom->GetCenter();
	return TOEvector3df(center.x, center.y, center.z);
}

TOEvector3df TFRoom::GetRotation(){
	TRoom* currentRoom = (TRoom*)m_entityNode;
	glm::vec3 rot = currentRoom->GetRotation();
	return TOEvector3df(rot.x, rot.y, rot.z);
}

TOEvector3df TFRoom::GetScale(){
	TRoom* currentRoom = (TRoom*)m_entityNode;
	glm::vec3 scale = currentRoom->GetSize();
	return TOEvector3df(scale.x, scale.y, scale.z);
}

float TFRoom::GetDistance(TOEvector3df position){
	TRoom* currentRoom = (TRoom*)m_entityNode;
	return currentRoom->GetDistance(glm::vec3(position.X, position.Y, position.Z));
}

TNode* TFRoom::GetConnectionNode(){
	return m_entityNode;
}

bool TFRoom::AddChild(TFNode* children){
	bool output = TFNode::AddChild(children);

	if(output && children->GetEntityType() == TLIGHT_ENTITY){
		VideoDriver::GetInstance()->GetSceneManager()->Light2Room(children);
		m_roomLights.push_back((TFLight*)children);
	}

	return output;
}

void TFRoom::DeleteLight(TFNode* light){
	int size = m_roomLights.size();
	for(int i=0; i<size; i++){
		if(m_roomLights[i] == light){
			m_roomLights.erase(m_roomLights.begin() + i);
			break;
		}
	}
}
