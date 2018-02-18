#include "TMesh.h"

#include <glm/gtc/type_ptr.hpp>
#include <stdexcept>
#include <iostream>
#include <chrono>

TMesh::TMesh(){
	m_program = NULL;
	m_mesh = TResourceManager::GetInstance()->GetResourceMesh("./../assets/models/Wizard.obj");
}

TMesh::~TMesh(){
}

void TMesh::BeginDraw(){
	// Bind and send the data to the VERTEX SHADER
	SendShaderData();

	// Bind and draw elements depending of how many vbos
	GLuint* elementsBuffer = m_mesh->GetElementBuffer();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *elementsBuffer);
	glDrawElements(GL_TRIANGLES, 10000, GL_UNSIGNED_INT, 0);
}

void TMesh::EndDraw(){
}

// PROVISIONAL FUNCTION
void TMesh::SetProgram(Program* prog){
	m_program = prog;
}

void TMesh::SendShaderData(){
	// If there is no Program, exit
	if(m_program == NULL) throw std::runtime_error("SHADER NOT ASSIGNED TO MESH");

    // BIND THE VERTEX
    GLuint* vertexBuffer = m_mesh->GetVertexBuffer();
	glBindBuffer(GL_ARRAY_BUFFER, *vertexBuffer);

	// SEND THE VERTEX
	GLint posAttrib = glGetAttribLocation(m_program->GetProgramID(), "VertexPosition");
	glVertexAttribPointer(posAttrib,3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
	glEnableVertexAttribArray(posAttrib);

	// BIND THE UV
    GLuint* UvBuffer = m_mesh->GetUvBuffer();
	glBindBuffer(GL_ARRAY_BUFFER, *UvBuffer);

	// SEND THE UV
	GLint uvAttrib = glGetAttribLocation(m_program->GetProgramID(), "inUV");
	glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);
	glEnableVertexAttribArray(uvAttrib);

	// SEND THE MODEL/VIEW/MATRIX
	GLint viewUniform = glGetUniformLocation(m_program->GetProgramID(), "ModelViewMatrix");
	glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(m_stack.top()));

	// BIND THE NORMAL
	// GLuint* NormalBuffer = m_mesh->GetNormalBuffer();
	// glBindBuffer(GL_ARRAY_BUFFER, *NormalBuffer);

	// SEND THE NORMAL
	// GLint normalAttrib = glGetAttribLocation(m_program->GetProgramID(), "vertexNormal");
	// glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(3*sizeof(float)));
	// glEnableVertexAttribArray(normalAttrib);
}
	