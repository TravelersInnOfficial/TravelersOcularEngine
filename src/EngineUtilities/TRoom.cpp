#include "./TRoom.h"
#include "./TPortal.h"
#include "./../TOcularEngine/VideoDriver.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <GL/glew.h>

TRoom::TRoom(glm::vec3 size, glm::vec3 center, glm::vec3 rotation):TNode(){
	drawed = false;

	m_size = size;
	m_center = center;
	m_rotation = rotation;
	m_transform = glm::mat4(1.0f);

	m_stackClipping[0] = +1.0f;
	m_stackClipping[1] = -1.0f;
	m_stackClipping[2] = +1.0f;
	m_stackClipping[3] = -1.0f;

	CalculateTransform();
}

TRoom::~TRoom(){
	// Delete all portals
	int size = m_portals.size();
	for(int i=0; i<size; i++){
		delete m_portals[i];
	}
	m_portals.clear();
}

void TRoom::Draw(){
	drawed = true;

	DrawDebug();

	TNode::Draw();
	
	int size = m_portals.size();
	for(int i=0; i<size; i++){
		TPortal* currentPortal = m_portals[i];
		PushClippingLimits();
		currentPortal->CheckVisibility();
		PopClippingLimits();
	}

	drawed = false;
}

void TRoom::PushClippingLimits(){
	m_stackClipping[0] = TEntity::m_clippingLimits[0];
	m_stackClipping[1] = TEntity::m_clippingLimits[1];
	m_stackClipping[2] = TEntity::m_clippingLimits[2];
	m_stackClipping[3] = TEntity::m_clippingLimits[3];
}

void TRoom::PopClippingLimits(){
	TEntity::m_clippingLimits[0] = m_stackClipping[0];
	TEntity::m_clippingLimits[1] = m_stackClipping[1];
	TEntity::m_clippingLimits[2] = m_stackClipping[2];
	TEntity::m_clippingLimits[3] = m_stackClipping[3];
}

TPortal* TRoom::AddPortal(TRoom* connection, glm::vec3 size, glm::vec3 center, glm::vec3 rotation){
	TPortal* portal = nullptr;
	if(connection != this){
		portal = new TPortal(this, connection, size, center, rotation);
		m_portals.push_back(portal);
	}
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
	glm::vec4 secondCorner = glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f);

	glm::vec4 auxPoint = glm::inverse(m_transform) * glm::vec4(point.x, point.y, point.z, 1.0f);
	point = glm::vec3(auxPoint.x, auxPoint.y, auxPoint.z);

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

		glm::vec3 diff = nearestPoint - point;
		diff = diff * m_size;

		return glm::length(diff);
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
	// 3º Translation
	m_transform = glm::translate(m_transform, glm::vec3(m_center.x, m_center.y, m_center.z));

	// 2º Rotation
	glm::quat axisX = glm::angleAxis(glm::radians(m_rotation.x), glm::vec3(1,0,0));
	glm::quat axisY = glm::angleAxis(glm::radians(m_rotation.y), glm::vec3(0,1,0));
	glm::quat axisZ = glm::angleAxis(glm::radians(m_rotation.z), glm::vec3(0,0,1));

	glm::quat crossed = glm::cross(axisZ, axisY);

 	glm::mat4 final1 = glm::toMat4(crossed);
 	glm::mat4 final2 = glm::toMat4(axisX);

 	m_transform =  m_transform * final1* final2;

 	// 1º Size
	m_transform = glm::scale(m_transform, glm::vec3(m_size.x, m_size.y, m_size.z));
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

void TRoom::DrawDebug(){
	Program* myProgram = VideoDriver::GetInstance()->SetShaderProgram(BB_SHADER);

	// Cube 1x1x1, centered on origin
	GLfloat vertices[] = {
		-0.5, -0.5, -0.5, 1.0,
		0.5, -0.5, -0.5, 1.0,
		0.5,  0.5, -0.5, 1.0,
		-0.5,  0.5, -0.5, 1.0,
		-0.5, -0.5,  0.5, 1.0,
		0.5, -0.5,  0.5, 1.0,
		0.5,  0.5,  0.5, 1.0,
		-0.5,  0.5,  0.5, 1.0,
	};

	GLuint vbo_vertices;
	glGenBuffers(1, &vbo_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLushort elements[] = {
		0, 1, 2, 3,
		4, 5, 6, 7,
		0, 4, 1, 5, 2, 6, 3, 7
	};
	GLuint ibo_elements;
	glGenBuffers(1, &ibo_elements);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	// Apply object's transformation matrix 
	glm::mat4 m = TEntity::ProjMatrix * TEntity::ViewMatrix * TEntity::m_stack.top() * m_transform;
	GLuint uniform_m = glGetUniformLocation(myProgram->GetProgramID(), "MVP");
	glUniformMatrix4fv(uniform_m, 1, GL_FALSE, &m[0][0]);

	// Send light color
	GLuint linecolor = glGetUniformLocation(myProgram->GetProgramID(), "LineColor");
	glUniform3fv(linecolor, 1, glm::value_ptr(glm::vec3(1.0f, 0.0f, 0.0f)));

	// Send each vertex data
	GLuint attribute_v_coord = glGetAttribLocation(myProgram->GetProgramID(), "VertexPosition");	
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glEnableVertexAttribArray(attribute_v_coord);

	glVertexAttribPointer(
		attribute_v_coord,  // attribute
		4,                  // number of elements per vertex, here (x,y,z,w)
		GL_FLOAT,           // the type of each element
		GL_FALSE,           // take our values as-is
		0,                  // no extra data between each position
		0                   // offset of first element
	);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, 0);
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, (GLvoid*)(4*sizeof(GLushort)));
	glDrawElements(GL_LINES, 8, GL_UNSIGNED_SHORT, (GLvoid*)(8*sizeof(GLushort)));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableVertexAttribArray(attribute_v_coord);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &vbo_vertices);
	glDeleteBuffers(1, &ibo_elements);
}



