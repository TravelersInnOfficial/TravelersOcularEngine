#include "TMesh.h"

#include <glm/gtc/type_ptr.hpp>
#include <stdexcept>
#include <iostream>
#include <chrono>

TMesh::TMesh(){

	/*std::vector<glm::vec3> vertices = {

        glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 0.0f),
        glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 0.0f),
        glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3(1.0f, 1.0f, 0.0f),
        glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3(1.0f, 1.0f, 0.0f),
        glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(1.0f, 1.0f, 0.0f),
        glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 0.0f),
        glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f)
    };*/

	// Definimos los elementos (los vertices en este caso), que vamos a usar
	/*elements = {
		0,1,2,		// Vertices 0, 1, 2
		0,1,3		// Vertices 0, 2, 3
	};*/

	// MOST IMPORTANT LINE (1 hour to find this error)
	m_program = NULL;
	m_mesh = TResourceManager::GetInstance()->GetResourceMesh("./../assets/models/wizard.obj");
	// Create vertex buffer for [vec3 vertexPosition, vec3 normalDirection, vec2 UVCoordinate]
	//m_vbo = 0;
	//glGenBuffers(1, &m_vbo);

	//m_ebo = 0;
	//glGenBuffers(1, &m_ebo);
	
	// Send vbo all of the vertices data
	//glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	// **This can be done is multiple ways**
	// ONE possible way is having a vertex array with all the information per vertex
	// [vec3 vertexPosition, vec3 normalDirection, vec2 UVCoordinate]
	// and send information with an offset 

	// Another possibility is creating 3 buffers one for each vector but needs 
	// its custom buffer data, and glVertexAttribPointer (with previous binding)
	
	// Send ebo all index of the faces (3 vertices)
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(float), &elements[0], GL_STATIC_DRAW);
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

	// vertex normal
	/*
	GLint normalAttrib = glGetAttribLocation(m_program->GetProgramID(), "vertexNormal");
	glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(normalAttrib);*/

	// uv texture
	GLint colorAttrib = glGetAttribLocation(m_program->GetProgramID(), "VertexColor");
	glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)(0*sizeof(float)));
	glEnableVertexAttribArray(colorAttrib);

	GLint viewUniform = glGetUniformLocation(m_program->GetProgramID(), "ModelViewMatrix");
	glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(m_stack.top()));
	//glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(m_stack.top()));
}
	