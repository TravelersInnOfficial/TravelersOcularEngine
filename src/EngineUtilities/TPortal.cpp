#include "./TPortal.h"
#include "./TRoom.h"
#include "./Entities/TEntity.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

int TPortal::Sign(int v){
	if(v>=0) return 1;
	else return -1;
}

TPortal::TPortal(TRoom* first, TRoom* second, glm::vec3 size, glm::vec3 center, glm::vec3 rotation){
	m_firstConnection = first;
	m_secondConnection = second;
	m_size = size;
	m_center = center;
	m_rotation = rotation;
	m_transform = glm::mat4(1.0f);

	CalculateTransform();
}

TPortal::~TPortal(){}

// COMPROBAR FUNCIONAMIENTO
void TPortal::CalculateTransform(){
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

bool TPortal::CheckVisibility(){
	bool output = true;

	// Se supone que el m_stack.top() debe estar como identidad, sin aplicar ninguna transformacion
	glm::mat4 mvp = TEntity::ProjMatrix * TEntity::ViewMatrix * TEntity::m_stack.top() * m_transform;

	int upDown, leftRight, nearFar;
	upDown = leftRight = nearFar = 0;

	for(int i= -1; i<=0; i++){
		// +X -X
		for(int j= -1; j<=0; j++){
			// +Y -Y
			for(int k= -1; k<=0; k++){
				// +Z -Z
				glm::vec3 point = glm::vec3(0.5f*Sign(i), 0.5f*Sign(j), 0.5f*Sign(k));
				glm::vec4 mvpPoint = mvp * glm::vec4(point.x, point.y, point.z, 1.0f);

				CheckVisibility(mvpPoint, &upDown, &leftRight, &nearFar);
			}
		}
	}

	// Comprobacion visibilidad
	int sides = 8;
	if(upDown == sides || upDown == -sides || leftRight == sides || leftRight == -sides || nearFar == sides){
		output = false;
	}

	// PINTAR LA SEGUNA HABITACION DE LA CONEXION SIEMPRE QUE AUN NO SE HAYA PINTADO
	if(output){
		if(!m_secondConnection->GetDrawed()){
			m_secondConnection->Draw();
		}
	}

	return output;
}

void TPortal::CheckVisibility(glm::vec4 point, int* upDown, int* leftRight, int* nearFar){
    if(point.x > point.w) (*leftRight)++;
    else if(point.x < -point.w) (*leftRight)--;

    if(point.y > point.w) (*upDown)++;
    else if(point.y < -point.w) (*upDown)--;

    if(point.z > point.w) (*nearFar)++;
    else if(point.z < 0) (*nearFar)--;
}


void TPortal::SetSize(glm::vec3 size){
	m_size = size;
	CalculateTransform();
}

void TPortal::SetCenter(glm::vec3 center){
	m_center = center;
	CalculateTransform();
}

void TPortal::SetRotation(glm::vec3 rot){
	m_rotation = rot;
	CalculateTransform();
}

