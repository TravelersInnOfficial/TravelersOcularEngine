#include "./TRoom.h"
#include "./TPortal.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

TRoom::TRoom(glm::vec3 size, glm::vec3 center, glm::vec3 rotation):TNode(){
	drawed = false;

	m_size = size;
	m_center = center;
	m_rotation = rotation;
	m_transform = glm::mat4(1.0f);

	CalculateTransform();
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
			delete currentPortal;
			m_portals.erase(m_portals.begin() + i);
			return true;
		}
	}
	return false;
}

bool TRoom::GetDrawed(){
	return drawed;
}

float TRoom::GetDistance(glm::vec3 point){
	glm::vec4 firstCorner = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	firstCorner = m_transform * firstCorner;

	glm::vec4 secondCorner = glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f);
	secondCorner = m_transform * secondCorner;

	// 1º Is Inside the cube?
		bool insideX = (point.x <= firstCorner.x && point.x >= secondCorner.x);
		bool insideY = (point.y <= firstCorner.y && point.y >= secondCorner.y);
		bool insideZ = (point.z <= firstCorner.z && point.z >= secondCorner.z);

		// The point is inside the box 
		if(insideX && insideY && insideZ){
			return 0.0f;
		}

	// 2º Distance to the cube
		float posX = NearestPoint(firstCorner.x, secondCorner.x, point.x);
		float posY = NearestPoint(firstCorner.y, secondCorner.y, point.y);
		float posZ = NearestPoint(firstCorner.z, secondCorner.z, point.z);
		glm::vec3 nearestPoint = glm::vec3(posX, posY, posZ);

		return glm::length(nearestPoint - point);
}

float TRoom::NearestPoint(float pointA, float pointB, float target){
	float output = 0.0f;

	if(target <= pointA && target >= pointB) output = target;
	else if(target > pointA) output = pointA;
	else if(target < pointB) output = pointB;

	return output;
}

void TRoom::SetSize(glm::vec3 size){
	m_size = size;
	CalculateTransform();
}

void TRoom::Scale(glm::vec3 size){
	m_size = m_size * size;
	CalculateTransform();
}

void TRoom::SetCenter(glm::vec3 center){
	m_center = center;
	CalculateTransform();
}

void TRoom::Translate(glm::vec3 center){
	m_center = m_center + center;
	CalculateTransform();
}

void TRoom::SetRotation(glm::vec3 rot){
	m_rotation = rot;
	CalculateTransform();
}

void TRoom::Rotate(glm::vec3 rot){
	m_rotation = m_rotation + rot;
	CalculateTransform();
}

void TRoom::CalculateTransform(){
	// 1º Size
	m_transform = glm::scale(m_transform, glm::vec3(m_size.x, m_size.y, m_size.z));

	// 2º Rotation
	glm::quat axisX = glm::angleAxis(glm::radians(m_rotation.x), glm::vec3(1,0,0));
	glm::quat axisY = glm::angleAxis(glm::radians(m_rotation.y), glm::vec3(0,1,0));
	glm::quat axisZ = glm::angleAxis(glm::radians(m_rotation.z), glm::vec3(0,0,1));

	glm::quat crossed = glm::cross(axisZ, axisY);

 	glm::mat4 final1 = glm::toMat4(crossed);
 	glm::mat4 final2 = glm::toMat4(axisX);

 	m_transform = final1 * m_transform * final2;

	// 3º Translation
	m_transform = glm::translate(m_transform, glm::vec3(m_center.x, m_center.y, m_center.z));
}

glm::vec3 TRoom::GetSize(){
	return m_size;
}

glm::vec3 TRoom::GetCenter(){
	return m_center;
}

glm::vec3 TRoom::GetRotation(){
	return m_rotation;
}
