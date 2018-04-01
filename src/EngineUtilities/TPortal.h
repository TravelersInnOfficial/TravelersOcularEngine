#ifndef TPORTAL_H
#define TPORTAL_H

#include <glm/gtc/type_ptr.hpp>

class TRoom;

class TPortal{
public:
	TPortal(TRoom* first, TRoom* second, glm::vec3 size, glm::vec3 center, glm::vec3 rot);
	~TPortal();

	// MOlaria que aparte de comprobar si la forma del portal se esta viendo
	// Calcular su como su caja en la pantalla
	bool CheckVisibility();
	void CheckVisibility(glm::vec4 point, int* upDown, int* leftRight, int* nearFar);
	void CalculateTransform();

	void SetSize(glm::vec3 size);
	void SetCenter(glm::vec3 center);
	void SetRotation(glm::vec3 rot);

private:
	int Sign(int v);

	// 1 -> 2
	TRoom* m_firstConnection;		// The first room in the connection
	TRoom* m_secondConnection;	// The second room in the connection

	// Forma del portal
	glm::mat4 m_transform;
	glm::vec3 m_size;
	glm::vec3 m_center;
	glm::vec3 m_rotation;

	// Los limites de clipping del portal
	float m_limits[4]; // MaxX MinX MaxY MinY
	void PrepareLimits();
	void ChangeEntityClipping();

	// DEBUG
	void DrawDebug();
};

#endif
