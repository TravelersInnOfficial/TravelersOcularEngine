#include "TLight.h"
#include "../TOcularEngine/VideoDriver.h"

#include <GL/glew.h>

TLight::TLight(TColor color, float attenuation){
	m_color = color;
	m_attenuation = attenuation;
	m_program = STANDARD_SHADER;
	m_active = true;
	drawBB = false;
	m_directional = false;
	m_direction =  TOEvector3df(0,-1,0);
}

TLight::~TLight(){}

void TLight::SetDirection( TOEvector3df direction){
	m_direction = direction;
}

 TOEvector3df TLight::GetDirection(){
	return m_direction;
}

void TLight::SetColor(TColor color){
	m_color = color;
}

TColor TLight::GetColor(){
	return m_color;
}

void TLight::SetAttenuation(float attenuation){
	m_attenuation = attenuation;
}

float TLight::GetAttenuation(){
	return m_attenuation;
}

void TLight::SetActive(bool active){
	m_active = active;
}

bool TLight::GetActive(){
	return m_active;
}

void TLight::SetDirectional(bool directional){
	m_directional = directional;
}

bool TLight::GetDirectional(){
	return m_directional;
}

void TLight::BeginDraw(){if(drawBB) DrawBB();}

void TLight::EndDraw(){}

// TODO: Optimize buffer by filling them only one time
void TLight::DrawBB(){
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
	
	//glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_mesh->GetCenter()) * glm::scale(glm::mat4(1), m_mesh->GetSize());

	// Apply object's transformation matrix 
	glm::mat4 m = ProjMatrix * ViewMatrix * m_stack.top();
	GLuint uniform_m = glGetUniformLocation(myProgram->GetProgramID(), "MVP");
	glUniformMatrix4fv(uniform_m, 1, GL_FALSE, &m[0][0]);

	// Send light color
	GLuint linecolor = glGetUniformLocation(myProgram->GetProgramID(), "LineColor");
	glUniform3f(linecolor, 0.7f, 0.7f, 0.0f);

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