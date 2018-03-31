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
	bool GetDrawed();

private:
	bool drawed;	// Esta habitacion ha sido ya dibujada? Si/No

	std::vector<TPortal*> m_portals;

	// Tamanyo de la habitacion
	glm::vec3 m_size;
	glm::vec3 m_center;
	glm::vec3 m_rotation;
};


#endif