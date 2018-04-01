#ifndef TROOM_H
#define TROOM_H

#include <vector>
#include "./TNode.h"
#include <glm/gtc/type_ptr.hpp>

class TPortal;

class TRoom: public TNode{
public:
	TRoom(glm::vec3 size, glm::vec3 center, glm::vec3 rotation);
	~TRoom();

	void Draw() override;
	TPortal* AddPortal(TRoom* connection, glm::vec3 size, glm::vec3 center, glm::vec3 rotation);
	bool DeletePortal(TPortal* portal);
	
	void SetSize(glm::vec3 size);
	void SetCenter(glm::vec3 center);
	void SetRotation(glm::vec3 rot);

	void Scale(glm::vec3 size);
	void Translate(glm::vec3 center);
	void Rotate(glm::vec3 rot);

	glm::vec3 GetSize();
	glm::vec3 GetCenter();
	glm::vec3 GetRotation();

	bool GetDrawed();
	float GetDistance(glm::vec3 point);

private:
	float NearestPoint(float pointA, float pointB, float target);
	void CalculateTransform();
	bool drawed;	// Esta habitacion ha sido ya dibujada? Si/No

	std::vector<TPortal*> m_portals;

	// Tamanyo de la habitacion
	glm::mat4 m_transform;
	glm::vec3 m_size;
	glm::vec3 m_center;
	glm::vec3 m_rotation;
};


#endif