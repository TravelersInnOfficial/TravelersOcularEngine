#include "TMesh.h"

#include <glm/gtc/type_ptr.hpp>
#include <stdexcept>
#include <iostream>
#include <chrono>

TMesh::TMesh(){
	// MOST IMPORTANT LINE (1 hour to find this error)
	m_program = NULL;
	m_mesh = TResourceManager::GetInstance()->GetResourceMesh("./../assets/models/Wizard.obj");
}

TMesh::~TMesh(){
	//std::cout << "Deleting MESH: "<< this << "\n";
	//glBindBuffer(GL_ARRAY_BUFFER, 0);	
	//glDeleteBuffers(1, &m_vbo);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);	
	//glDeleteBuffers(1, &m_ebo);
}

void TMesh::BeginDraw(){
    // Send all attributes and uniforms to shader
    GLuint* vertexBuffer = m_mesh->GetVertexBuffer();
	glBindBuffer(GL_ARRAY_BUFFER, *vertexBuffer);
	//GLuint* elementsBuffer = m_mesh->GetElementBuffer();

	SendShaderData();

	GLuint* elementsBuffer = m_mesh->GetElementBuffer();
	// Bind and draw elements depending of how many vbos
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *elementsBuffer);
	glDrawElements(GL_TRIANGLES, 10000, GL_UNSIGNED_INT, 0);   

	//glDrawArrays(GL_TRIANGLES, 0, m_mesh->GetVertexSize());
}

void TMesh::EndDraw(){
	// This method is empty
}

// PROVISIONAL FUNCTION
void TMesh::SetProgram(Program* prog){
	m_program = prog;
}

void TMesh::SendShaderData(){
	// If there is no Program, exit
	if(m_program == NULL){
		throw std::runtime_error("SHADER NOT ASSIGNED TO MESH");
	}

	// vertex position
	GLint posAttrib = glGetAttribLocation(m_program->GetProgramID(), "VertexPosition");
	glVertexAttribPointer(posAttrib,3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
	glEnableVertexAttribArray(posAttrib);

	// uv texture
	GLint colorAttrib = glGetAttribLocation(m_program->GetProgramID(), "VertexColor");
	glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)(0*sizeof(float)));
	glEnableVertexAttribArray(colorAttrib);

	GLint viewUniform = glGetUniformLocation(m_program->GetProgramID(), "ModelViewMatrix");
	glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(m_stack.top()));
}
	